#ifndef _CABBAGECOLLIDER_CSCENEMANAGER_H_INCLUDED_
#define _CABBAGECOLLIDER_CSCENEMANAGER_H_INCLUDED_

#include <list>

#include "CSceneObject.h"
#include "CMeshSceneObject.h"
#include "CFrameBufferObject.h"
#include "CSceneEffectManager.h"
#include "CPerspectiveCameraSceneObject.h"

#include "IScene.h"

#include <SLine3.h>
#include <SColor.h>
#include <SPosition2.h>
#define THIS_OBJECT_WILL_NEVER_MOVE_AND_ITS_BOUNDING_BOX_IS_CORRECT 3945210

#include <SUniform.h>
#include <SAttribute.h>


class CLight
{
	// CLight should implement ISceneObject
	// that way light billboards will be drawable by using a scene->set debug flag
	// and positioning,etc will be inheritted

public:

	SColorAf Color;
	SVector3f Position;
	float Radius;

	SUniformReference<SColorAf> BindColor;
	SUniformReference<SVector3f> BindPosition;
	SUniformReference<float> BindRadius;

	// Todo: change values only through get/set, set scene changed when so

	CLight()
		: BindColor(Color), BindPosition(Position), BindRadius(Radius), Radius(25.f)
	{}

};

class CScene : public IScene
{

	static CLight const NullLight;

protected:

	CPerspectiveCameraSceneObject DefaultCamera;
	ICameraSceneObject * ActiveCamera;

	glm::mat4 ViewMatrix, ProjMatrix;
	int LightCount;

	SUniformReference<glm::mat4> BindViewMatrix, BindProjMatrix;
	SUniformReference<int> BindLightCount;

	std::map<std::string, boost::shared_ptr<IUniform const> > Uniforms;

	ISceneObject RootObject;

	bool UseCulling;

public:

	CScene();

	ICameraSceneObject * const getActiveCamera();
	ICameraSceneObject const * const getActiveCamera() const;
	void setActiveCamera(ICameraSceneObject * const activeCamera);

	template <typename T>
	void addUniform(std::string const & label, T const & uniform)
	{
		Uniforms[label] = boost::shared_ptr<SUniform<T> >(new SUniformReference<T>(uniform));
	}
	void addUniform(std::string const & label, boost::shared_ptr<IUniform const> const uniform);
	void removeUniform(std::string const & label);
	
	virtual boost::shared_ptr<IAttribute const> const getAttribute(std::string const & label) const;

	boost::shared_ptr<IUniform const> const getUniform(std::string const & label) const;

	void update();

	std::vector<CLight *> Lights;
	bool SceneChanged;

	bool const isCullingEnabled() const;
	void setCullingEnabled(bool const culling);

	void setUseHierarchy(bool h);
	bool getUseHierarchy();
	void toggleUseHierarchy();

	void enableDebugData(EDebugData::Domain const type);
	void disableDebugData(EDebugData::Domain const type);

};

class CApplication;

class CSceneManager : public CScene
{

	CScene * CurrentScene;

	CFrameBufferObject * SceneFrameBuffer;
	CTexture * SceneFrameTexture;
	CRenderBufferObject * SceneDepthBuffer;
	CShader * QuadCopy;

	CSceneEffectManager * EffectManager, * DeferredManager, * DefaultManager;

	SSize2 ScreenSize;

public:

	CSceneManager(SPosition2 const & screenSize);
	void init(bool const EffectsManager = true, bool const FrameBuffer = true);

	void addSceneObject(ISceneObject * sceneObject);
	void removeSceneObject(ISceneObject * sceneObject);

	void removeAllSceneObjects();

	CMeshSceneObject * addMeshSceneObject(CMesh * Mesh);
	CMeshSceneObject * addMeshSceneObject(CMesh * Mesh, CShader * Shader, CShader * DeferredShader);
	CMeshSceneObject * addMeshSceneObject(CMesh * Mesh, CShader * Shader, CShader * DeferredShader, CRenderable::SMaterial const & Material);
	CMeshSceneObject * addMeshSceneObject(std::string const & Mesh, std::string const & Shader, std::string const & DeferredShader, CRenderable::SMaterial const & Material);

	void drawAll();
	void endDraw();

	void load(); // Deprecated
	void load(ERenderPass const Pass);

	CFrameBufferObject * getSceneFrameBuffer();
	CTexture * getSceneFrameTexture();
	CRenderBufferObject * getSceneDepthBuffer();

	CSceneEffectManager * getEffectManager();
	void setEffectManager(CSceneEffectManager * effectManager);

	SSize2 const & getScreenSize() const;

	void setDeferred(bool const isDeferred);
	
	static GLuint const getQuadHandle();

};
#endif
