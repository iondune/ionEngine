#include "CPerspectiveCameraSceneObject.h"


void CPerspectiveCameraSceneObject::UpdateProjection()
{
    ProjectionMatrix = glm::perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
}

CPerspectiveCameraSceneObject::CPerspectiveCameraSceneObject(float const aspectRatio, float const Near, float const Far, float const FOV)
{
    SetProjection(FOV, aspectRatio, Near, Far);
}

void CPerspectiveCameraSceneObject::SetProjection(float const FOV, float const aspectRatio, float const Near, float const Far)
{
	FieldOfView = FOV;
	AspectRatio = aspectRatio;
	NearPlane = Near;
	FarPlane = Far;

	UpdateProjection();
}

f32 CPerspectiveCameraSceneObject::GetFieldOfView() const
{
	return FieldOfView;
}

f32 CPerspectiveCameraSceneObject::GetAspectRatio() const
{
	return AspectRatio;
}

f32 CPerspectiveCameraSceneObject::GetNearPlane() const
{
	return NearPlane;
}

f32 CPerspectiveCameraSceneObject::GetFarPlane() const
{
	return FarPlane;
}

void CPerspectiveCameraSceneObject::SetFieldOfView(f32 const fieldOfView)
{
	FieldOfView = fieldOfView;
	UpdateProjection();
}

void CPerspectiveCameraSceneObject::SetAspectRatio(f32 const aspectRatio)
{
	AspectRatio = aspectRatio;
	UpdateProjection();
}

void CPerspectiveCameraSceneObject::SetNearPlane(f32 const nearPlane)
{
	NearPlane = nearPlane;
	UpdateProjection();
}

void CPerspectiveCameraSceneObject::SetFarPlane(f32 const farPlane)
{
	FarPlane = farPlane;
	UpdateProjection();
}
