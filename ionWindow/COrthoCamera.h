#ifndef _CABBAGE_SCENE_CORTHOCAMERA_H_INCLUDED_
#define _CABBAGE_SCENE_CORTHOCAMERA_H_INCLUDED_

#include <SVector3.h>
#include <glm/glm.hpp>

#include <CCameraSceneObject.h>

class COrthoCamera : public CCameraSceneObject
{

public:

	COrthoCamera(float const Near, float const Far);

    COrthoCamera(float const Left, float const Right, float const Bottom, float const Top, float const Near, float const Far);

    virtual void setProjection(float const Left, float const Right, float const Bottom, float const Top, float const Near, float const Far);

};

#endif
