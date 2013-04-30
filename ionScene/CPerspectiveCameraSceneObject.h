#ifndef _ION_SCENE_CPERSPECTIVECAMERASCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CPERSPECTIVECAMERASCENEOBJECT_H_INCLUDED_

#include "CCameraSceneObject.h"


class CPerspectiveCameraSceneObject : public CCameraSceneObject
{

public:

    CPerspectiveCameraSceneObject(float const AspectRatio = 16.f/9.f, float const Near = 0.1f, float const Far = 100.f, float const FOV = 60.f);

    virtual void setProjection(float const FOV, float const AspectRatio, float const Near, float const Far);

};

#endif
