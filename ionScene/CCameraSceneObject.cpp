#include "CCameraSceneObject.h"

#include <glm/gtc/matrix_transform.hpp>


CCameraSceneObject::CCameraSceneObject()
    : LookDirection(0, 0, 1), UpVector(0, 1, 0)
{
    RecalculateViewMatrix();
}

void CCameraSceneObject::RecalculateViewMatrix()
{
	ViewMatrix = glm::lookAt(getPosition().GetGLMVector(), (getPosition() + LookDirection).GetGLMVector(), UpVector.GetGLMVector());
}

SVector3f const & CCameraSceneObject::GetLookDirecton() const
{
    return LookDirection;
}

SVector3f const CCameraSceneObject::GetLookAtTarget() const
{
	return getPosition() + LookDirection;
}

SVector3f const CCameraSceneObject::GetUpVector() const
{
	return UpVector;
}

void CCameraSceneObject::SetLookDirection(SVector3f const & lookDirection)
{
    LookDirection = lookDirection;
}

void CCameraSceneObject::SetLookAtTarget(SVector3f const & lookAtTarget)
{
	SetLookDirection(lookAtTarget - getPosition());
}

void CCameraSceneObject::SetUpVector(SVector3f const & upVector)
{
	UpVector = upVector;
}

glm::mat4 const & CCameraSceneObject::GetViewMatrix() const
{
    return ViewMatrix;
}

glm::mat4 const & CCameraSceneObject::GetProjectionMatrix() const
{
    return ProjectionMatrix;
}

void CCameraSceneObject::SetViewMatrix(glm::mat4 const & viewMatrix)
{
	ViewMatrix = viewMatrix;
}

void CCameraSceneObject::SetProjectionMatrix(glm::mat4 const & projectionMatrix)
{
	ProjectionMatrix = projectionMatrix;
}
