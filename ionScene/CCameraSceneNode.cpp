
#include "CCameraSceneNode.h"


CCameraSceneNode::CCameraSceneNode()
    : LookDirection(0, 0, 1), UpVector(0, 1, 0),
	ViewDirty(false), ProjectionDirty(false)
{
    RecalculateViewMatrix();
}

void CCameraSceneNode::RecalculateViewMatrix()
{
	ViewMatrix = glm::lookAt(GetPosition().GetGLMVector(), (GetPosition() + LookDirection).GetGLMVector(), UpVector.GetGLMVector());
	ViewDirty = false;
}

void CCameraSceneNode::Update()
{
	if (ViewDirty)
		RecalculateViewMatrix();
	if (ProjectionDirty)
		RecalculateProjectionMatrix();

	ISceneNode::Update();
}

vec3f CCameraSceneNode::GetLookDirecton() const
{
    return LookDirection;
}

vec3f CCameraSceneNode::GetLookAtTarget() const
{
	return GetPosition() + LookDirection;
}

vec3f CCameraSceneNode::GetUpVector() const
{
	return UpVector;
}

void CCameraSceneNode::SetLookDirection(vec3f const & lookDirection)
{
    LookDirection = lookDirection;
}

void CCameraSceneNode::SetLookAtTarget(vec3f const & lookAtTarget)
{
	SetLookDirection(lookAtTarget - GetPosition());
}

void CCameraSceneNode::SetUpVector(vec3f const & upVector)
{
	UpVector = upVector;
}

glm::mat4 CCameraSceneNode::GetViewMatrix() const
{
    return ViewMatrix;
}

glm::mat4 CCameraSceneNode::GetProjectionMatrix() const
{
    return ProjectionMatrix;
}

void CCameraSceneNode::SetViewMatrix(glm::mat4 const & viewMatrix)
{
	ViewMatrix = viewMatrix;
}

void CCameraSceneNode::SetProjectionMatrix(glm::mat4 const & projectionMatrix)
{
	ProjectionMatrix = projectionMatrix;
}
