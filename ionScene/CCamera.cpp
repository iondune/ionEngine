
#include "CCamera.h"


CCamera::CCamera()
    : LookDirection(0, 0, 1), UpVector(0, 1, 0),
	ViewDirty(false), ProjectionDirty(false)
{
    RecalculateViewMatrix();
}

void CCamera::RecalculateViewMatrix()
{
	ViewMatrix = glm::lookAt(GetPosition().GetGLMVector(), (GetPosition() + LookDirection).GetGLMVector(), UpVector.GetGLMVector());
	ViewDirty = false;
}

void CCamera::Update()
{
	if (ViewDirty)
		RecalculateViewMatrix();
	if (ProjectionDirty)
		RecalculateProjectionMatrix();

	ISceneNode::Update();
}

vec3f CCamera::GetLookDirecton() const
{
    return LookDirection;
}

vec3f CCamera::GetLookAtTarget() const
{
	return GetPosition() + LookDirection;
}

vec3f CCamera::GetUpVector() const
{
	return UpVector;
}

void CCamera::SetLookDirection(vec3f const & lookDirection)
{
    LookDirection = lookDirection;
}

void CCamera::SetLookAtTarget(vec3f const & lookAtTarget)
{
	SetLookDirection(lookAtTarget - GetPosition());
}

void CCamera::SetUpVector(vec3f const & upVector)
{
	UpVector = upVector;
}

glm::mat4 CCamera::GetViewMatrix() const
{
    return ViewMatrix;
}

glm::mat4 CCamera::GetProjectionMatrix() const
{
    return ProjectionMatrix;
}

void CCamera::SetViewMatrix(glm::mat4 const & viewMatrix)
{
	ViewMatrix = viewMatrix;
}

void CCamera::SetProjectionMatrix(glm::mat4 const & projectionMatrix)
{
	ProjectionMatrix = projectionMatrix;
}
