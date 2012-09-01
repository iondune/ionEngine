#ifndef _ION_SCENE_CSCENEMANAGER_H_INCLUDED_
#define _ION_SCENE_CSCENEMANAGER_H_INCLUDED_

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

#include "CDefaultColorRenderPass.h"
#include "CMultiOutRenderPass.h"


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

	void OnWindowResized(SPosition2 const & screenSize);

	void drawAll();
	void endDraw();

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
