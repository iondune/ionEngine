
#pragma once

#include <ionMath/SVector3.h>
#include <ionScene/CCameraSceneObject.h>
#include <glm/glm.hpp>


class COrthoCamera : public CCameraSceneObject
{

public:

	COrthoCamera(float const Near, float const Far);

    COrthoCamera(float const Left, float const Right, float const Bottom, float const Top, float const Near, float const Far);

    virtual void setProjection(float const Left, float const Right, float const Bottom, float const Top, float const Near, float const Far);

};
