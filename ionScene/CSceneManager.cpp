#include "CSceneManager.h"

#include <algorithm>
#include <sstream>

#include "CShaderLoader.h"
#include "CMeshLoader.h"
#include "CTextureLoader.h"

#include "CDeferredShadingManager.h"


CLight const CScene::NullLight;


CScene::CScene()
	: BindProjMatrix(ProjMatrix), BindViewMatrix(ViewMatrix), BindLightCount(LightCount), UseCulling(true)
{
	ActiveCamera = & DefaultCamera;

	addUniform("uProjMatrix", ProjMatrix);
	addUniform("uViewMatrix", ViewMatrix);
	addUniform("uLightCount", LightCount);

	RootObject.setCullingEnabled(false);
}

void CScene::addUniform(std::string const & label, boost::shared_ptr<IUniform const> const uniform)
{
	Uniforms[label] = uniform;
}

void CScene::removeUniform(std::string const & label)
{
	std::map<std::string, boost::shared_ptr<IUniform const> >::iterator it = Uniforms.find(label);

	if (it != Uniforms.end())
		Uniforms.erase(it);
}

ICameraSceneObject * const CScene::getActiveCamera()
{
	return ActiveCamera;
}

ICameraSceneObject const * const CScene::getActiveCamera() const
{
	return ActiveCamera;
}

void CScene::setActiveCamera(ICameraSceneObject * const activeCamera)
{
	ActiveCamera = activeCamera;
}

bool const CScene::isCullingEnabled() const
{
	return UseCulling;
}

void CScene::setCullingEnabled(bool const culling)
{
	UseCulling = culling;
}

boost::shared_ptr<IAttribute const> const CScene::getAttribute(std::string const & label) const
{
	return boost::shared_ptr<IAttribute const>();
}

unsigned int const digitCount(int n)
{
	int count = 1;
	if (n < 0)
	{
		n *= -1;
		++ count;
	}

	while (n > 10)
	{
		++ count;
		n /= 10;
	}

	return count;
}

boost::shared_ptr<IUniform const> const CScene::getUniform(std::string const & label) const
{
	if (label.substr(0, 8) == "uLights[")
	{
		std::stringstream ss(label.substr(8));
		unsigned int index;
		ss >> index;
		std::string remaining = ss.str();
		remaining = remaining.substr(2 + digitCount(index));

		if (remaining == "Color")
		{
			if (index >= Lights.size())
				return BindUniform(NullLight.Color);
			else
				return BindUniform(Lights[index]->Color);
		}
		else if (remaining == "Position")
		{
			if (index >= Lights.size())
				return BindUniform(NullLight.Position);
			else
				return BindUniform(Lights[index]->Position);
		}
	}

	std::map<std::string, boost::shared_ptr<IUniform const> >::const_iterator it = Uniforms.find(label);

	if (it != Uniforms.end())
		return it->second;

	return boost::shared_ptr<IUniform const>();
}

void CScene::update()
{
	ActiveCamera->recalculateViewMatrix();
	ViewMatrix = ActiveCamera->getViewMatrix();
	ProjMatrix = ActiveCamera->getProjectionMatrix();

	if (LightCount != Lights.size())
	{
		SceneChanged = true;
		LightCount = Lights.size();
	}

	RootObject.updateAbsoluteTransformation();
	RootObject.update();
}

GLuint CSceneManager::QuadHandle = 0;

CSceneManager::CSceneManager(SPosition2 const & screenSize)
	: FinalBlurSize(0.0f), SceneFrameBuffer(0),
	EffectManager(0), ScreenSize(screenSize)
{
	CurrentScene = this;

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
	

	STextureCreationFlags Flags;
	Flags.MipMaps = false;
	Flags.Wrap = GL_CLAMP_TO_EDGE;
	SceneFrameTexture = new CTexture(ScreenSize, true, Flags);
	SceneDepthBuffer = new CRenderBufferObject(GL_DEPTH_COMPONENT24, ScreenSize);

	SceneFrameBuffer = new CFrameBufferObject();
	SceneFrameBuffer->attach(SceneDepthBuffer, GL_DEPTH_ATTACHMENT);
	SceneFrameBuffer->attach(SceneFrameTexture, GL_COLOR_ATTACHMENT0);

	if (! SceneFrameBuffer->isValid())
		std::cerr << "Failed to make FBO for scene drawing!!!!!!" << std::endl  << std::endl  << std::endl;

	EffectManager = DefaultManager = new CSceneEffectManager(this);
	if (EffectManager)
		EffectManager->setEffectEnabled(ESE_BLOOM, true);

	DeferredManager = new CDeferredShadingManager(this);

	BlurHorizontal = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "BlurH.frag");
}

void CSceneManager::addSceneObject(ISceneObject * sceneObject)
{
	RootObject.addChild(sceneObject);
}

void CSceneManager::removeSceneObject(ISceneObject * sceneObject)
{
	RootObject.removeChild(sceneObject);
}

void CSceneManager::removeAllSceneObjects()
{
	RootObject.removeChildren();
}

bool sortISOXY (ISceneObject* a, ISceneObject* b)
{
	SVector3f av = a->getAbsoluteBoundingBox().MinCorner;//getWorldBoundingBoxMinPoint();
	SVector3f bv = b->getAbsoluteBoundingBox().MaxCorner;//
	if(av.X == bv.X) {
		return av.Y < bv.Y;
	}
	else return av.X < bv.X;
}

void CSceneManager::drawAll()
{
	printOpenGLErrors("beginning of draw");
	ISceneObject::resetObjectCounts();
	CurrentScene->update();

	printOpenGLErrors("pre traversal");
	if (EffectManager)
	{
		for (std::vector<CSceneEffectManager::SRenderPass>::iterator it = EffectManager->RenderPasses.begin(); it != EffectManager->RenderPasses.end(); ++ it)
		{
			if (it->Target)
				it->Target->bind();
			else
				glBindFramebuffer(GL_FRAMEBUFFER, 0);

			if (it->Pass == ERenderPass::DeferredLights)
			{
				glClearColor(0.f,0.f,0.f,0.f);
				glDisable(GL_DEPTH_TEST);
				glEnable(GL_BLEND);
				glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);
			}

			//if (it->Pass != ERenderPass::Default)
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
			printOpenGLErrors("begining load");
			load(it->Pass);
			printOpenGLErrors("begining traversal");
			RootObject.draw(CurrentScene, it->Pass, UseCulling);
			printOpenGLErrors("after traversal");

			if (it->Pass != ERenderPass::DeferredLights) {
				//glEnable(GL_ALPHA);
				glEnable(GL_BLEND);
				glEnable(GL_DEPTH_TEST);
				glDepthMask(GL_FALSE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else {
			}
			
			if (it->Pass != ERenderPass::DeferredLights) {
				//glBlendFunc(GL_ONE, GL_MAX);
				printOpenGLErrors("after blend func");
				glDepthMask(GL_TRUE);
				printOpenGLErrors("after depth mask");
				glDisable(GL_BLEND);
				printOpenGLErrors("after disable blend");
				//glDisable(GL_ALPHA);
				printOpenGLErrors("after disable alpha");
			}

			if (it->Pass == ERenderPass::DeferredLights)
			{
				glDisable(GL_BLEND);
				glEnable(GL_DEPTH_TEST);
			}
			printOpenGLErrors("after deferred");
		}
		printOpenGLErrors("before effects");

		EffectManager->apply();
	}
	else
	{
		SceneFrameBuffer->bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_ALPHA);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		RootObject.load(CurrentScene, ERenderPass::Default);
		RootObject.draw(CurrentScene, ERenderPass::Default, UseCulling);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA);
	}
	printOpenGLErrors("after effects");

	SceneChanged = false;

	SceneFrameBuffer->bind();
	//printf("Num objects: %d\n", numObjects);

	
	printOpenGLErrors("end of drawall");
}

void CSceneManager::blurSceneIn(float seconds, float const RunTime)
{
	std::cout << "Blurring in scene..." << std::endl;
	BlurOutTime = 0;
	BlurInTime = seconds;
	CurTime = RunTime;
}

#include <CApplication.h>
void CSceneManager::endDraw()
{
	// Do fade-in
	if (CurTime == -1.0f)
		Dim = 1.0f;

	if (BlurInTime > 0.0f)
	{
		FinalBlurSize = 0.0f;
		Dim = std::max(1.0f - (BlurInTime - (CApplication::get().getRunTime() - CurTime))/BlurInTime, 0.0f);
		if ((CApplication::get().getRunTime() - CurTime) > BlurInTime)
		{
			BlurInTime = 0.0f;
			CurTime = -1.0f;
		}
	}


	// Draw to screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	// THE FINAL RENDER
	{
		CShaderContext Context(* BlurHorizontal);

		Context.bindTexture("uTexColor", SceneFrameTexture);
		Context.uniform("BlurSize", FinalBlurSize);
		Context.uniform("DimAmount", Dim);
		Context.bindBufferObject("aPosition", QuadHandle, 2);

		glDrawArrays(GL_QUADS, 0, 4);
	}

	glEnable(GL_DEPTH_TEST);

	printOpenGLErrors("end of enddraw");
}

CMeshSceneObject * CSceneManager::addMeshSceneObject(CMesh * Mesh)
{
	CMeshSceneObject * Object = new CMeshSceneObject();
	Object->setMesh(Mesh);
	addSceneObject(Object);
	return Object;
}

CMeshSceneObject * CSceneManager::addMeshSceneObject(CMesh * Mesh, CShader * Shader, CShader * DeferredShader)
{
	CMeshSceneObject * Object = new CMeshSceneObject();
	Object->setMesh(Mesh);
	Object->setShader(ERenderPass::Default, Shader);
	Object->setShader(ERenderPass::DeferredColors, DeferredShader);
	addSceneObject(Object);
	return Object;
}

CMeshSceneObject * CSceneManager::addMeshSceneObject(CMesh * Mesh, CShader * Shader, CShader * DeferredShader, CRenderable::SMaterial const & Material)
{
	CMeshSceneObject * Object = new CMeshSceneObject();
	Object->setMesh(Mesh);
	Object->setShader(ERenderPass::Default, Shader);
	Object->setShader(ERenderPass::DeferredColors, DeferredShader);
	Object->setMaterial(Material);
	addSceneObject(Object);
	return Object;
}

CMeshSceneObject * CSceneManager::addMeshSceneObject(std::string const & Mesh, std::string const & Shader, std::string const & DeferredShader, CRenderable::SMaterial const & Material)
{
	CMeshSceneObject * Object = new CMeshSceneObject();
	Object->setMesh(CMeshLoader::load3dsMesh(Mesh));
	Object->setShader(ERenderPass::Default, CShaderLoader::loadShader(Shader));
	Object->setShader(ERenderPass::DeferredColors, CShaderLoader::loadShader(DeferredShader));
	Object->setMaterial(Material);
	addSceneObject(Object);
	return Object;
}



void CScene::enableDebugData(EDebugData::Domain const type)
{
	RootObject.enableDebugData(type);
}

void CScene::disableDebugData(EDebugData::Domain const type)
{
	RootObject.disableDebugData(type);
}


void CSceneManager::load()
{
	RootObject.load(this, ERenderPass::Default);
}

void CSceneManager::load(ERenderPass const Pass)
{
	RootObject.load(this, Pass);
}

CFrameBufferObject * CSceneManager::getSceneFrameBuffer()
{
	return SceneFrameBuffer;
}

CTexture * CSceneManager::getSceneFrameTexture()
{
	return SceneFrameTexture;
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

GLuint const CSceneManager::getQuadHandle()
{
	return QuadHandle;
}

SSize2 const & CSceneManager::getScreenSize() const
{
	return ScreenSize;
}

void CSceneManager::setDeferred(bool const isDeferred)
{
	EffectManager->setEffectEnabled(ESE_ALL, false);
	if (isDeferred)
		EffectManager = DeferredManager;
	else
		EffectManager = DefaultManager;
}
