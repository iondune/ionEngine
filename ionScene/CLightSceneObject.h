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
	CLightSceneObject();
	
	// Attributes //

	SColorAf const & getColor() const;
	f32 const getRadius() const;

	void setColor(SColorAf const & color);
	void setRadius(f32 const radius);

	// Variable Bindings //

	smartPtr<SUniformReference<SColorAf> const> const getColorBind() const;
	smartPtr<SUniformReference<SVector3f> const> const getPositionBind() const;
	smartPtr<SUniformReference<f32> const> const getRadiusBind() const;

};

#endif
