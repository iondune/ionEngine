#include "COrthoCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "CApplication.h"

COrthoCamera::COrthoCamera(float const Near, float const Far)
{
	SPosition2 ScreenSize = CApplication::get().getWindowSize();
    setProjection(-ScreenSize.X / 2.f, ScreenSize.X / 2.f, -ScreenSize.Y / 2.f, ScreenSize.Y / 2.f, Near, Far);
}

COrthoCamera::COrthoCamera(float const Left, float const Right, float const Bottom, float const Top, float const Near, float const Far)
{
    setProjection(Left, Right, Bottom, Top, Near, Far);
}

void COrthoCamera::setProjection(float const Left, float const Right, float const Bottom, float const Top, float const Near, float const Far)
{
	ProjectionMatrix = glm::ortho(Left, Right, Bottom, Top, Near, Far);
}
