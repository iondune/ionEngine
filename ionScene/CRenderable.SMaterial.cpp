#include "CRenderable.h"


CRenderable::SMaterial::SMaterial()
{
	loadDefaults();
}

void CRenderable::SMaterial::loadDefaults()
{
	Shininess = 1000.0f;
	AmbientColor = SColorf(0.15f, 0.15f, 0.15f);
	DiffuseColor = SColorf(0.8f, 0.8f, 0.8f);
	SpecularColor = SColorf(1.f, 1.f, 1.f);
}

void CRenderable::SMaterial::setTexture(unsigned int const Layer, CTexture * const Texture)
{
	if (Layer >= Textures.size())
		Textures.resize(Layer + 1, 0);
	Textures[Layer] = Texture;

	auto it = Textures.end();

	while (it != Textures.begin())
	{
		it --;
		if (* it)
			break;
		it = Textures.erase(it);
	}
}
