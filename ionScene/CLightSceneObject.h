#ifndef _ION_SCENE_CLIGHTSCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CLIGHTSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include <ionGraphics/SUniform.h>


class CLightSceneObject : public ISceneObject
{

	color3f Color;
	f32 Radius;

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
