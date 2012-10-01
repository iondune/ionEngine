#include "CLightSceneObject.h"


/////////////////
// Constructor //
/////////////////

CLightSceneObject::CLightSceneObject(color3f const & color, f32 const radius)
	: Radius(radius), Color(color)
{}


////////////////
// Attributes //
////////////////
	
color3f const & CLightSceneObject::getColor() const
{
	return Color;
}

f32 const & CLightSceneObject::getRadius() const
{
	return Radius;
}


void CLightSceneObject::setColor(color3f const & color)
{
	Color = color;
}

void CLightSceneObject::setRadius(f32 const radius)
{
	Radius = radius;
}
