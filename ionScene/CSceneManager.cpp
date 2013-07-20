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

CSceneManager::CSceneManager(vec2i const & screenSize)
	: SceneFrameTexture(0), SceneDepthTexture(0), SceneFrameBuffer(0),
	EffectManager(0), DefaultManager(0), 
	ScreenSize(screenSize)
{
	CurrentScene = this;
	DefaultColorRenderPass = smartNew(new CDefaultColorRenderPass());

	addUniform("uScreenSize", BindUniformReference(ScreenSize));
}

void CSceneManager::OnWindowResized(vec2i const & screenSize)
{
	ScreenSize = screenSize;
	if (SceneFrameBuffer)
	{
		delete SceneFrameBuffer;
		delete SceneFrameTexture;
		delete SceneDepthTexture;

		SceneFrameBuffer = 0;
		SceneFrameTexture = 0;
		SceneDepthTexture = 0;

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
			printOpenGLErrors("SceneManager :: Create Frame Texture");
			Flags.PixelFormat = GL_DEPTH_COMPONENT;
			Flags.PixelInternalFormat = GL_DEPTH_COMPONENT;
			SceneDepthTexture = new CTexture(ScreenSize, true, Flags);
			printOpenGLErrors("SceneManager :: Create Depth Texture");
		}

		SceneFrameBuffer = new CFrameBufferObject();
		SceneFrameBuffer->attachColorTexture(SceneFrameTexture, 0);
		SceneFrameBuffer->attachDepthTexture(SceneDepthTexture);
		printOpenGLErrors("SceneManager :: Create Frame Buffer");

		/*SceneFrameBuffer->bind();
		GLenum Buffers[] = 
		{
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1
		};

		glDrawBuffers(sizeof(Buffers)/sizeof(GLenum), Buffers);*/

		if (! SceneFrameBuffer->isValid())
		{
			std::cerr << "Failed to make FBO for scene drawing!" << std::endl << std::endl << std::endl;

			delete SceneFrameBuffer;
			SceneFrameBuffer = 0;
			delete SceneFrameTexture;
			SceneFrameTexture = 0;
			delete SceneDepthTexture;
			SceneDepthTexture = 0;
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
				delete SceneDepthTexture;
				SceneDepthTexture = 0;
			}
		}

		DefaultColorRenderPass->setFrameBuffer(SceneFrameBuffer);

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

smartPtr<CDefaultColorRenderPass> CSceneManager::getDefaultColorRenderPass()
{
	return DefaultColorRenderPass;
}

void CSceneManager::drawAll()
{
	ISceneObject::resetObjectCounts();
	CurrentScene->update();

	if (EffectManager && SceneFrameBuffer)
	{
		for (auto it = EffectManager->RenderPasses.begin(); it != EffectManager->RenderPasses.end(); ++ it)
		{
			(* it)->onPreDraw();
			CurrentScene->load(* it);
			CurrentScene->draw(* it);
			(* it)->onPostDraw();
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

CSceneEffectManager * CSceneManager::getEffectManager()
{
	return EffectManager;
}

void CSceneManager::setEffectManager(CSceneEffectManager * effectManager)
{
	EffectManager = effectManager;
}

vec2i const & CSceneManager::getScreenSize() const
{
	return ScreenSize;
}
