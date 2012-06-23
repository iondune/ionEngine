#include "CPerspectiveCameraSceneObject.h"


CPerspectiveCameraSceneObject::CPerspectiveCameraSceneObject(float const AspectRatio, float const Near, float const Far, float const FOV)
{
    setProjection(FOV, AspectRatio, Near, Far);
}

void CPerspectiveCameraSceneObject::setProjection(float const FOV, float const AspectRatio, float const Near, float const Far)
{
    ProjectionMatrix = glm::perspective(FOV, AspectRatio, Near, Far);
}
