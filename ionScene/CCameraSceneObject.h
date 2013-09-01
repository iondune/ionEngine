
#pragma once

#include "ionConfig.h"

#include "ICameraSceneObject.h"


class CCameraSceneObject : public ICameraSceneObject
{

public:

	CCameraSceneObject();

	virtual void RecalculateViewMatrix();

	virtual SVector3f const & GetLookDirecton() const;
	virtual SVector3f const GetLookAtTarget() const;
	virtual SVector3f const GetUpVector() const;

	virtual void SetLookDirection(SVector3f const & lookDirection);
	virtual void SetLookAtTarget(SVector3f const & lookAtTarget);
	virtual void SetUpVector(SVector3f const & UpVector);

	virtual glm::mat4 const & GetViewMatrix() const;
	virtual glm::mat4 const & GetProjectionMatrix() const;

	virtual void SetViewMatrix(glm::mat4 const & viewMatrix);
	virtual void SetProjectionMatrix(glm::mat4 const & projectionMatrix);

protected:

	SVector3f LookDirection;
	SVector3f UpVector;

	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

};
