#ifndef _ION_SCENE_ICAMERASCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_ICAMERASCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"


class ICameraSceneObject : public ISceneObject
{

public:

	virtual void recalculateViewMatrix() =0;

	virtual SVector3f const & getLookDirecton() const =0;
	virtual SVector3f const getLookAtTarget() const =0;

	virtual void setLookDirection(SVector3f const & lookDirection) =0;
	virtual void setLookAtTarget(SVector3f const & lookAtTarget) =0;

	virtual glm::mat4 const & getViewMatrix() const =0;
	virtual glm::mat4 const & getProjectionMatrix() const =0;

};

#endif
