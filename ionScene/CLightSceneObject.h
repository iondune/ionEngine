#ifndef _ION_SCENE_CLIGHTSCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CLIGHTSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include "SUniform.h"


class CLightSceneObject : public ISceneObject
{

	SColorAf Color;
	f32 Radius;

	SUniformReference<SColorAf> ColorBind;
	SUniformReference<SVector3f> PositionBind; // To Do : This should be updated per-draw using the absolute transformation * origin
	SUniformReference<f32> RadiusBind;

public:

	//! Constructor
	CLightSceneObject(color4f const & color = color4f(1.f), f32 const radius = 25.f);
	
	// Attributes //

	SColorAf const & getColor() const;
	f32 const & getRadius() const;

	void setColor(SColorAf const & color);
	void setRadius(f32 const radius);

};

#endif
