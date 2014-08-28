
#include "SMaterial.h"


SMaterial::SMaterial()
{
	LoadDefaults();
}

void SMaterial::LoadDefaults()
{
	Shininess = 1000.0f;
	Ambient = SColorf(0.05f);
	Diffuse = SColorf(0.9f);
	Specular = SColorf(1.f);
}

void SMaterial::SetTexture(uint const Layer, ion::GL::Texture * const Texture)
{
	if (Layer >= Textures.size())
		Textures.resize(Layer + 1, 0);
	Textures[Layer] = Texture;

	// Clean dangling nulls from unused layers
	auto it = Textures.end();
	while (it != Textures.begin())
	{
		it --;
		if (* it)
			break;
		it = Textures.erase(it);
	}
}
