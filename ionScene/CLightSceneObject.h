#ifndef _ION_SCENE_CLIGHTSCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CLIGHTSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include "SUniform.h"


class CLightSceneObject : public ISceneObject
{

	color3f Color;
	f32 Radius;

	SUniformReference<color3f> ColorBind;
	SUniformReference<vec3f> PositionBind; // To Do : This should be updated per-draw using the absolute transformation * origin
	SUniformReference<f32> RadiusBind;

public:

	//! Constructor
	CLightSceneObject(color3f const & color = color3f(1.f), f32 const radius = 25.f);
	
	// Attributes //

	color3f const & getColor() const;
	f32 const & getRadius() const;

	void setColor(color3f const & color);
	void setRadius(f32 const radius);

};

#endif
