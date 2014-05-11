
#include "CPerspectiveCamera.h"


CPerspectiveCamera::CPerspectiveCamera(f32 const aspectRatio, f32 const nearPlane, f32 const farPlane, f32 const focalLength)
	: AspectRatio(aspectRatio), NearPlane(nearPlane), FarPlane(farPlane), FocalLength(focalLength)
{}

void CPerspectiveCamera::UpdateProjectionMatrix()
{
	ProjectionMatrix = glm::perspective<f32>(GetFieldOfView(), AspectRatio, NearPlane, FarPlane);
	ProjectionDirty = false;
}

f32 CPerspectiveCamera::GetFieldOfView() const
{
	return RadiansToDegrees(ArcTan(0.5f / FocalLength));
}

f32 CPerspectiveCamera::GetFocalLength() const
{
	return FocalLength;
}

f32 CPerspectiveCamera::GetAspectRatio() const
{
	return AspectRatio;
}

f32 CPerspectiveCamera::GetNearPlane() const
{
	return NearPlane;
}

f32 CPerspectiveCamera::GetFarPlane() const
{
	return FarPlane;
}

void CPerspectiveCamera::SetFocalLength(f32 const focalLength)
{
	FocalLength = focalLength;
}

void CPerspectiveCamera::SetFieldOfView(f32 const fieldOfView)
{
	FocalLength = 0.5f / Tan(DegreesToRadians(fieldOfView));
}

void CPerspectiveCamera::SetAspectRatio(f32 const aspectRatio)
{
	AspectRatio = aspectRatio;
}

void CPerspectiveCamera::SetNearPlane(f32 const nearPlane)
{
	NearPlane = nearPlane;
}

void CPerspectiveCamera::SetFarPlane(f32 const farPlane)
{
	FarPlane = farPlane;
}
