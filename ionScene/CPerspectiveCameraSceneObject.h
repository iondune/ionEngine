#ifndef _ION_SCENE_CPERSPECTIVECAMERASCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CPERSPECTIVECAMERASCENEOBJECT_H_INCLUDED_

#include "CCameraSceneObject.h"


class CPerspectiveCameraSceneObject : public CCameraSceneObject
{

protected:

	f32 FieldOfView;
	f32 AspectRatio;
	f32 NearPlane, FarPlane;

	void UpdateProjection();

public:

    CPerspectiveCameraSceneObject(float const aspectRatio = 16.f/9.f, float const Near = 0.1f, float const Far = 100.f, float const FOV = 60.f);

    virtual void SetProjection(float const FOV, float const aspectRatio, float const Near, float const Far);

	f32 GetFieldOfView() const;
	f32 GetAspectRatio() const;
	f32 GetNearPlane() const;
	f32 GetFarPlane() const;

	void SetFieldOfView(f32 const fieldOfView);
	void SetAspectRatio(f32 const aspectRatio);
	void SetNearPlane(f32 const nearPlane);
	void SetFarPlane(f32 const farPlane);

};

#endif
