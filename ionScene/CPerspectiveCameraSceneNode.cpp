
#include "CPerspectiveCameraSceneNode.h"


CPerspectiveCameraSceneNode::CPerspectiveCameraSceneNode(f32 const aspectRatio, f32 const nearPlane, f32 const farPlane, f32 const focalLength)
	: AspectRatio(aspectRatio), NearPlane(nearPlane), FarPlane(farPlane), FocalLength(focalLength)
{}

void CPerspectiveCameraSceneNode::UpdateProjectionMatrix()
{
	ProjectionMatrix = glm::perspective<f32>(GetFieldOfView(), AspectRatio, NearPlane, FarPlane);
	ProjectionDirty = false;
}

f32 CPerspectiveCameraSceneNode::GetFieldOfView() const
{
	return RadiansToDegrees(ArcTan(0.5f / FocalLength));
}

f32 CPerspectiveCameraSceneNode::GetFocalLength() const
{
	return FocalLength;
}

f32 CPerspectiveCameraSceneNode::GetAspectRatio() const
{
	return AspectRatio;
}

f32 CPerspectiveCameraSceneNode::GetNearPlane() const
{
	return NearPlane;
}

f32 CPerspectiveCameraSceneNode::GetFarPlane() const
{
	return FarPlane;
}

void CPerspectiveCameraSceneNode::SetFocalLength(f32 const focalLength)
{
	FocalLength = focalLength;
}

void CPerspectiveCameraSceneNode::SetFieldOfView(f32 const fieldOfView)
{
	FocalLength = 0.5f / Tan(DegreesToRadians(fieldOfView));
}

void CPerspectiveCameraSceneNode::SetAspectRatio(f32 const aspectRatio)
{
	AspectRatio = aspectRatio;
}

void CPerspectiveCameraSceneNode::SetNearPlane(f32 const nearPlane)
{
	NearPlane = nearPlane;
}

void CPerspectiveCameraSceneNode::SetFarPlane(f32 const farPlane)
{
	FarPlane = farPlane;
}
