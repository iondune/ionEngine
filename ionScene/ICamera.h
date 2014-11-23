
#pragma once

#include "CSceneNode.h"


class ICamera : public ISceneNode
{

public:
	
	ICamera(ISceneNode * Parent)
		: ISceneNode(Parent)
	{}
	
	virtual void RecalculateViewMatrix() = 0;
	virtual void RecalculateProjectionMatrix() = 0;

	virtual vec3f GetLookDirecton() const = 0;
	virtual vec3f GetLookAtTarget() const = 0;
	virtual vec3f GetUpVector() const = 0;
	//virtual f32 GetFocalLength() const = 0;
	//virtual f32 GetFieldOfView() const = 0;
	virtual glm::mat4 GetViewMatrix() const = 0;
	virtual glm::mat4 GetProjectionMatrix() const = 0;
	
	virtual f32 GetNearPlane() const = 0;
	virtual f32 GetFarPlane() const = 0;
	//virtual void SetFieldOfView(f32 const fieldOfView) = 0;
	//virtual void SetFocalLength(f32 const focalLength) = 0;
	virtual void SetLookDirection(vec3f const & lookDirection) = 0;
	virtual void SetLookAtTarget(vec3f const & lookAtTarget) = 0;
	virtual void SetUpVector(vec3f const & upVector) = 0;
	virtual void SetViewMatrix(glm::mat4 const & viewMatrix) = 0;
	virtual void SetProjectionMatrix(glm::mat4 const & projectionMatrix) = 0;

};
