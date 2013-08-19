#ifndef _ION_SCENE_CSCENE_H_INCLUDED_
#define _ION_SCENE_CSCENE_H_INCLUDED_

#include "ionConfig.h"

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
		
		SLightBinding();
		SLightBinding(CLightSceneObject const * const LightObject);
		void bind(CLightSceneObject const * const LightObject);
		void unbind();

		sharedPtr<SUniformReference<vec3f> > PositionBind;
		sharedPtr<SUniformReference<f32> > RadiusBind;
		sharedPtr<SUniformReference<color3f> > ColorBind;
	};

protected:
	
	//! Camera used for drawing
	ICameraSceneObject * ActiveCamera;

	//! Default camrea to use if no other camera is specified
	CPerspectiveCameraSceneObject DefaultCamera;

	//! Camera-defined matricies
	glm::mat4 ViewMatrix, ProjMatrix;

	//! Light bindings
	//! Mutable to allow array expansion when accessing an out-of-bounds light binding
	mutable std::vector<SLightBinding> LightBindings;

	//! Uniform variable bindings
	std::map<std::string, sharedPtr<IUniform const> > Uniforms;

	//! Root of object tree
	ISceneObject RootObject;

	//! Whether scene should use trivial-reject culling in hierarchy operations
	bool UseCulling;

	s32 LightCount;
	vec3f CameraPosition;

public:

	CScene();


	////////////
	// Camera //
	////////////

	virtual ICameraSceneObject * const getActiveCamera();
	virtual ICameraSceneObject const * const getActiveCamera() const;
	virtual void setActiveCamera(ICameraSceneObject * const activeCamera);


	//////////////////////
	// Shader Variables //
	//////////////////////

	virtual void addUniform(std::string const & label, sharedPtr<IUniform const> const uniform);
	virtual void removeUniform(std::string const & label);
	
	virtual sharedPtr<IAttribute const> const getAttribute(std::string const & label) const;
	virtual sharedPtr<IUniform const> const getUniform(std::string const & label) const;


	////////////
	// Update //
	////////////

	virtual void update();
	virtual void load(sharedPtr<IRenderPass> const Pass);
	virtual void draw(sharedPtr<IRenderPass> const Pass);


	/////////////
	// Details //
	/////////////

	virtual void addSceneObject(ISceneObject * sceneObject);
	virtual void removeSceneObject(ISceneObject * sceneObject);
	virtual void removeAllSceneObjects();

	virtual bool const isCullingEnabled() const;
	virtual void setCullingEnabled(bool const culling);
	
	virtual bool const isDebugDataEnabled(EDebugData const type) const;
	virtual void enableDebugData(EDebugData const type);
	virtual void disableDebugData(EDebugData const type);


	///////////////////
	// Light Binding //
	///////////////////

	SLightBinding & getLightBinding(u32 const index);
	SLightBinding const & getLightBinding(u32 const index) const;
	u32 const getLightBindingCount() const;


};

#endif
