
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGL.h>


class SMaterial
{

public:

	SMaterial();
	void LoadDefaults();
	void SetTexture(uint const Layer, ion::GL::Texture * const Texture);

	vector<ion::GL::Texture *> Textures;

	color3f Ambient, Diffuse, Specular;
	f32 Shininess;

};
