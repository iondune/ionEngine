#include "CSceneManager.h"

#include <algorithm>
#include <sstream>

#include "CShaderLoader.h"
#include "CMeshLoader.h"
#include "CTextureLoader.h"

#include "CDeferredShadingManager.h"


GLuint const CSceneManager::getQuadHandle()
{
	static GLuint QuadHandle = 0;
	
	// Create a simple quad VBO to use for draw operations!
	if (! QuadHandle)
	{
		GLfloat QuadVertices[] = 
		{
			-1.0, -1.0,
			1.0, -1.0,
			1.0,  1.0,
			-1.0,  1.0
		};

		glGenBuffers(1, & QuadHandle);
		glBindBuffer(GL_ARRAY_BUFFER, QuadHandle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertices), QuadVertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	return QuadHandle;
}

CSceneManager::CSceneManager(SPosition2 const & screenSize)
	: SceneFrameTexture(0), SceneDepthBuffer(0), SceneFrameBuffer(0),
	EffectManager(0), DefaultManager(0), 
	ScreenSize(screenSize)
{
	CurrentScene = this;
	DefaultColorRenderPass = new CDefaultColorRenderPass();
}

void CSceneManager::OnWindowResized(SPosition2 const & screenSize)
{
	ScreenSize = screenSize;
	if (SceneFrameBuffer)
	{
		delete SceneFrameBuffer;
		delete SceneFrameTexture;
		delete SceneDepthBuffer;

		SceneFrameBuffer = 0;
		SceneFrameTexture = 0;
		SceneDepthBuffer = 0;

		init(false, true);
	}

	if (EffectManager)
	{
		EffectManager->OnWindowResized();
	}
}

void CSceneManager::init(bool const EffectsManager, bool const FrameBuffer)
{
	if (FrameBuffer)
	{
		// Create special framebuffer for draw operations
		{
			STextureCreationFlags Flags;
			Flags.MipMaps = false;
			Flags.Wrap = GL_CLAMP_TO_EDGE;
			SceneFrameTexture = new CTexture(ScreenSize, true, Flags);
			Flags.PixelInternalFormat = GL_R32F;
			SceneDepthTexture = new CTexture(ScreenSize, true, Flags);
		}
		SceneDepthBuffer = new CRenderBufferObject(GL_DEPTH_COMPONENT24, ScreenSize);

		SceneFrameBuffer = new CFrameBufferObject();
		SceneFrameBuffer->attach(SceneDepthBuffer, GL_DEPTH_ATTACHMENT);
		SceneFrameBuffer->attach(SceneFrameTexture, GL_COLOR_ATTACHMENT0);
		SceneFrameBuffer->attach(SceneDepthTexture, GL_COLOR_ATTACHMENT1);

		SceneFrameBuffer->bind();
		GLenum Buffers[] = 
		{
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1
		};

		glDrawBuffers(sizeof(Buffers)/sizeof(GLenum), Buffers);

		if (! SceneFrameBuffer->isValid())
		{
			std::cerr << "Failed to make FBO for scene drawing!" << std::endl << std::endl << std::endl;

			delete SceneFrameBuffer;
			SceneFrameBuffer = 0;
			delete SceneFrameTexture;
			SceneFrameTexture = 0;
			delete SceneDepthBuffer;
			SceneDepthBuffer = 0;
		}
		else
		{
			QuadCopy = CShaderLoader::loadShader("FBO/QuadCopy");

			if (! QuadCopy)
			{
				std::cerr << "Failed to load copy shader for scene drawing!" << std::endl << std::endl << std::endl;

				delete SceneFrameBuffer;
				SceneFrameBuffer = 0;
				delete SceneFrameTexture;
				SceneFrameTexture = 0;
				delete SceneDepthBuffer;
				SceneDepthBuffer = 0;
			}
		}

		getQuadHandle();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


	// Set default effect manager and initialize
	if (EffectsManager)
	{
		EffectManager = DefaultManager = new CSceneEffectManager(this);

		// If effects manager failed to load, revert to no-effects
		if (! EffectManager->isLoaded())
		{
			delete EffectManager;
			EffectManager = 0;
		}

		// Default-enable bloom
		//if (EffectManager)
		//	EffectManager->setEffectEnabled(ESE_BLOOM, true);

		// Setup deferred effecst manager
		//DeferredManager = new CDeferredShadingManager(this);
	}
}

void CSceneManager::drawAll()
{
	ISceneObject::resetObjectCounts();
	CurrentScene->update();

	if (EffectManager && SceneFrameBuffer)
	{
		for (std::vector<CSceneEffectManager::SRenderPass>::iterator it = EffectManager->RenderPasses.begin(); it != EffectManager->RenderPasses.end(); ++ it)
		{
			it->Pass->onPreDraw();
			CurrentScene->load(it->Pass);
			CurrentScene->draw(it->Pass);
			it->Pass->onPostDraw();
		}

		EffectManager->apply();

		SceneFrameBuffer->bind();
	}
	else
	{
		DefaultColorRenderPass->onPreDraw();
		CurrentScene->load(DefaultColorRenderPass);
		CurrentScene->draw(DefaultColorRenderPass);
		DefaultColorRenderPass->onPostDraw();

		if (SceneFrameBuffer)
			SceneFrameBuffer->bind();
	}
	
	printOpenGLErrors("Scene Manager :: Draw All");
}

void CSceneManager::endDraw()
{
	if (SceneFrameBuffer)
	{
		// Draw to screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDisable(GL_DEPTH_TEST);
		{
			CShaderContext Context(* QuadCopy);
			Context.bindTexture("uTexColor", SceneFrameTexture);
			Context.bindBufferObject("aPosition", getQuadHandle(), 2);

			glDrawArrays(GL_QUADS, 0, 4);
		}
		glEnable(GL_DEPTH_TEST);
	}

	printOpenGLErrors("Scene Manager :: End Draw");
}


void CScene::enableDebugData(EDebugData::Domain const type)
{
	RootObject.enableDebugData(type);
}

void CScene::disableDebugData(EDebugData::Domain const type)
{
	RootObject.disableDebugData(type);
}

CFrameBufferObject * CSceneManager::getSceneFrameBuffer()
{
	return SceneFrameBuffer;
}

CTexture * CSceneManager::getSceneFrameTexture()
{
	return SceneFrameTexture;
}

CTexture * CSceneManager::getSceneDepthTexture()
{
	return SceneDepthTexture;
}

CRenderBufferObject * CSceneManager::getSceneDepthBuffer()
{
	return SceneDepthBuffer;
}

CSceneEffectManager * CSceneManager::getEffectManager()
{
	return EffectManager;
}

void CSceneManager::setEffectManager(CSceneEffectManager * effectManager)
{
	EffectManager = effectManager;
}

SSize2 const & CSceneManager::getScreenSize() const
{
	return ScreenSize;
}
