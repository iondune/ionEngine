#ifndef _CABBAGECOLLIDER_CSCENEMANAGER_H_INCLUDED_
#define _CABBAGECOLLIDER_CSCENEMANAGER_H_INCLUDED_

#include <list>

#include "CSceneObject.h"
#include "CMeshSceneObject.h"
#include "CFrameBufferObject.h"
#include "CSceneEffectManager.h"
#include "CPerspectiveCameraSceneObject.h"
#include "CScene.h"

#include <SLine3.h>
#include <SColor.h>
#include <SPosition2.h>
#include <SUniform.h>
#include <SAttribute.h>


class CDefaultColorRenderPass : public IRenderPass
{

protected:

	CFrameBufferObject * FrameBuffer;

public:

	CDefaultColorRenderPass()
		: FrameBuffer(0)
	{}

	virtual void onPreDraw()
	{
		if (FrameBuffer)
			FrameBuffer->bind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	virtual void onPostDraw()
	{
		if (FrameBuffer)
			FrameBuffer->unbind();
	}

	virtual void onPreDrawObject(ISceneObject * Object)
	{}

	virtual void onPostDrawObject(ISceneObject * Object)
	{}

};

class CMultiOutRenderPass : public IRenderPass
{

protected:

	CFrameBufferObject * FrameBuffer;

public:

	CMultiOutRenderPass()
		: FrameBuffer(0)
	{}

	virtual void onPreDraw()
	{
		if (FrameBuffer)
			FrameBuffer->bind();

		float DepthClearColor[] = {1.f, 1.f, 1.f, 1.f};
		glClearBufferfv(GL_COLOR, 0, DepthClearColor);
		glClearBufferfv(GL_COLOR, 1, DepthClearColor);
	}

	virtual void onPostDraw()
	{
		if (FrameBuffer)
			FrameBuffer->unbind();
	}

	virtual void onPreDrawObject(ISceneObject * Object)
	{}

	virtual void onPostDrawObject(ISceneObject * Object)
	{}

};


class CApplication;

class CSceneManager : public CScene
{

	IScene * CurrentScene;

	CFrameBufferObject * SceneFrameBuffer;
	CTexture * SceneFrameTexture, * SceneDepthTexture;
	CRenderBufferObject * SceneDepthBuffer;
	CShader * QuadCopy;

	CSceneEffectManager * EffectManager, * DeferredManager, * DefaultManager;

	SSize2 ScreenSize;

	smartPtr<CDefaultColorRenderPass> DefaultColorRenderPass;

public:

	CSceneManager(SPosition2 const & screenSize);
	void init(bool const EffectsManager = true, bool const FrameBuffer = true);

	void addSceneObject(ISceneObject * sceneObject);
	void removeSceneObject(ISceneObject * sceneObject);

	void removeAllSceneObjects();

	void OnWindowResized(SPosition2 const & screenSize);

	CMeshSceneObject * addMeshSceneObject(CMesh * Mesh);
	CMeshSceneObject * addMeshSceneObject(CMesh * Mesh, CShader * Shader, CShader * DeferredShader);
	CMeshSceneObject * addMeshSceneObject(CMesh * Mesh, CShader * Shader, CShader * DeferredShader, CRenderable::SMaterial const & Material);
	CMeshSceneObject * addMeshSceneObject(std::string const & Mesh, std::string const & Shader, std::string const & DeferredShader, CRenderable::SMaterial const & Material);

	void drawAll();
	void endDraw();

	void load(IRenderPass const Pass);

	CFrameBufferObject * getSceneFrameBuffer();
	CTexture * getSceneFrameTexture();
	CTexture * getSceneDepthTexture();
	CRenderBufferObject * getSceneDepthBuffer();

	CSceneEffectManager * getEffectManager();
	void setEffectManager(CSceneEffectManager * effectManager);

	SSize2 const & getScreenSize() const;	
	static GLuint const getQuadHandle();

};

#endif
