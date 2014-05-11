
#pragma once

#include "ICameraSceneNode.h"


class CCameraSceneNode : public ICameraSceneNode
{

public:

	CCameraSceneNode();

	virtual void RecalculateViewMatrix();
	virtual void Update();

	virtual vec3f GetLookDirecton() const;
	virtual vec3f GetLookAtTarget() const;
	virtual vec3f GetUpVector() const;
	virtual glm::mat4 GetViewMatrix() const;
	virtual glm::mat4 GetProjectionMatrix() const;

	virtual void SetLookDirection(vec3f const & lookDirection);
	virtual void SetLookAtTarget(vec3f const & lookAtTarget);
	virtual void SetUpVector(vec3f const & UpVector);
	virtual void SetViewMatrix(glm::mat4 const & viewMatrix);
	virtual void SetProjectionMatrix(glm::mat4 const & projectionMatrix);

protected:

	vec3f LookDirection;
	vec3f UpVector;

	bool ViewDirty, ProjectionDirty;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

};
