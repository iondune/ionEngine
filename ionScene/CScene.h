#ifndef _ION_SCENE_CSCENE_H_INCLUDED_
#define _ION_SCENE_CSCENE_H_INCLUDED_

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

#include <SUniform.h>
#include <SAttribute.h>


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

#endif
