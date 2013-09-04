
#pragma once

#include "ISceneObject.h"


class ICameraSceneObject : public ISceneObject
{

public:

	virtual void RecalculateViewMatrix() =0;

	virtual SVector3f const & GetLookDirecton() const =0;
	virtual SVector3f const GetLookAtTarget() const =0;

	virtual void SetLookDirection(SVector3f const & lookDirection) =0;
	virtual void SetLookAtTarget(SVector3f const & lookAtTarget) =0;

	virtual glm::mat4 const & GetViewMatrix() const =0;
	virtual glm::mat4 const & GetProjectionMatrix() const =0;

	virtual void SetViewMatrix(glm::mat4 const & viewMatrix) =0;
	virtual void SetProjectionMatrix(glm::mat4 const & projectionMatrix) =0;

};
