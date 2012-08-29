#include "CLightSceneObject.h"

/////////////////
// Constructor //
/////////////////

CLightSceneObject::CLightSceneObject()
	: ColorBind(Color), PositionBind(Translation), RadiusBind(Radius), Radius(25.f)
{}


////////////////
// Attributes //
////////////////
	
SColorAf const & CLightSceneObject::getColor() const
{
	return Color;
}

f32 const CLightSceneObject::getRadius() const
{
	return Radius;
}


void CLightSceneObject::setColor(SColorAf const & color)
{
	Color = color;
}

void CLightSceneObject::setRadius(f32 const radius)
{
	Radius = radius;
}


///////////////////////
// Variable Bindings //
///////////////////////

smartPtr<SUniformReference<SColorAf> const> const CLightSceneObject::getColorBind() const
{
	return staticPtr<SUniformReference<SColorAf> const>(& ColorBind);
}

smartPtr<SUniformReference<SVector3f> const> const CLightSceneObject::getPositionBind() const
{
	return staticPtr<SUniformReference<SVector3f> const>(& PositionBind);
}

smartPtr<SUniformReference<f32> const> const CLightSceneObject::getRadiusBind() const
{
	return staticPtr<SUniformReference<f32> const>(& RadiusBind);
}
