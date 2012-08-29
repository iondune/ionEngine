#ifndef _ION_SCENE_CSCENE_H_INCLUDED_
#define _ION_SCENE_CSCENE_H_INCLUDED_

#include "IScene.h"
#include "ISceneObject.h"
#include "CLightSceneObject.h"

#include "ICameraSceneObject.h"
#include "CPerspectiveCameraSceneObject.h"


class CScene : public IScene
{

public:

	struct SLightBinding
	{
		static CLightSceneObject const NullLight;

		SLightBinding(CLightSceneObject const * const LightObject);
		void bind(CLightSceneObject const * const LightObject);

		SUniformReference<vec3f> PositionBind;
		SUniformReference<f32> RadiusBind;
		SUniformReference<color4f> ColorBind;

		smartPtr<SUniformReference<vec3f> > getPositionBind();
		smartPtr<SUniformReference<f32> > getRadiusBind();
		smartPtr<SUniformReference<color4f> > getColorBind();
	};

protected:
	
	//! Camera used for drawing
	ICameraSceneObject * ActiveCamera;

	//! Default camrea to use if no other camera is specified
	CPerspectiveCameraSceneObject DefaultCamera;

	//! Camera-defined matricies
	glm::mat4 ViewMatrix, ProjMatrix;

	//! Light bindings
	std::vector<SLightBinding> LightBindings;

	//! Light count bindings
	s32 LightCount;
	SUniformReference<s32> BindLightCount;

	//! Bind camera matrices
	SUniformReference<glm::mat4> BindViewMatrix, BindProjMatrix;

	//! Uniform variable bindings
	std::map<std::string, smartPtr<IUniform const> > Uniforms;

	//! Root of object tree
	ISceneObject RootObject;

	//! Whether scene should use trivial-reject culling in hierarchy operations
	bool UseCulling;

public:

	CScene();

	virtual ICameraSceneObject * const getActiveCamera();
	virtual ICameraSceneObject const * const getActiveCamera() const;
	virtual void setActiveCamera(ICameraSceneObject * const activeCamera);

	virtual void addUniform(std::string const & label, smartPtr<IUniform const> const uniform);
	virtual void removeUniform(std::string const & label);
	
	virtual smartPtr<IAttribute const> const getAttribute(std::string const & label) const;
	virtual smartPtr<IUniform const> const getUniform(std::string const & label) const;

	virtual void update();

	bool const isCullingEnabled() const;
	void setCullingEnabled(bool const culling);

	void enableDebugData(EDebugData::Domain const type);
	void disableDebugData(EDebugData::Domain const type);

};

#endif
