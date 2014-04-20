
#pragma once

#include <ionMath.h>
#include <ionGraphics/CTexture.h>


class SMaterial
{

public:

	SMaterial();
	void LoadDefaults();
	void SetTexture(uint const Layer, CTexture * const Texture);

	std::vector<CTexture *> Textures;

	color3f Ambient, Diffuse, Specular;
	f32 Shininess;

};
