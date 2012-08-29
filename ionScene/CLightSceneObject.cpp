#include "CLightSceneObject.h"

/////////////////
// Constructor //
/////////////////

CLightSceneObject::CLightSceneObject(color4f const & color, f32 const radius)
	: ColorBind(Color), PositionBind(Translation), RadiusBind(Radius), 
	Radius(radius), Color(color)
{}


////////////////
// Attributes //
////////////////
	
SColorAf const & CLightSceneObject::getColor() const
{
	return Color;
}

f32 const & CLightSceneObject::getRadius() const
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
