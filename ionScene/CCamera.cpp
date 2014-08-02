
#include "CCamera.h"


CCamera::CCamera(ISceneNode * Parent)
: ICamera(Parent)
{
	this->LookDirection = vec3f(0, 0, 1);
	this->UpVector = vec3f(0, 1, 0);

    RecalculateViewMatrix();
}

void CCamera::RecalculateViewMatrix()
{
	ViewMatrix = glm::lookAt(GetPosition().GetGLMVector(), (GetPosition() + LookDirection).GetGLMVector(), UpVector.GetGLMVector());
}

void CCamera::Update()
{
	RecalculateViewMatrix();
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
