
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>

#include "IUniform.h"


class SMaterial
{

public:

	SMaterial();
	void LoadDefaults();
	void SetTexture(uint const Layer, ion::GL::Texture * const Texture);

	vector<ion::GL::Texture *> Textures;

	CUniformValue<color3f> Ambient, Diffuse, Specular;
	CUniformValue<f32> Shininess;

};
