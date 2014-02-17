#include "CPerspectiveCameraSceneObject.h"


void CPerspectiveCameraSceneObject::UpdateProjection()
{
	ProjectionMatrix = glm::perspective<f32>(atan(0.5f / FocalLength) * 360.f / Constants32::Pi, AspectRatio, NearPlane, FarPlane);
}

CPerspectiveCameraSceneObject::CPerspectiveCameraSceneObject(float const aspectRatio, float const nearPlane, float const farPlane, float const focalLength)
	: AspectRatio(aspectRatio), NearPlane(nearPlane), FarPlane(farPlane), FocalLength(focalLength)
{
	UpdateProjection();
}

f32 CPerspectiveCameraSceneObject::GetFieldOfView() const
{
	return atan(0.5f / FocalLength) * 360.f / Constants32::Pi;
}

f32 CPerspectiveCameraSceneObject::GetFocalLength() const
{
	return FocalLength;
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

void CPerspectiveCameraSceneObject::SetFocalLength(f32 const focalLength)
{
	FocalLength = focalLength;
}

void CPerspectiveCameraSceneObject::SetFieldOfView(f32 const fieldOfView)
{
	FocalLength = 0.5f / tan(fieldOfView * Constants32::Pi / 360.f);
}

void CPerspectiveCameraSceneObject::SetAspectRatio(f32 const aspectRatio)
{
	AspectRatio = aspectRatio;
}

void CPerspectiveCameraSceneObject::SetNearPlane(f32 const nearPlane)
{
	NearPlane = nearPlane;
}

void CPerspectiveCameraSceneObject::SetFarPlane(f32 const farPlane)
{
	FarPlane = farPlane;
}
