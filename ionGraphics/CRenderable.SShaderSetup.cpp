#include "CRenderable.h"


CRenderable::SShaderSetup::SShaderSetup()
	: Loaded(false)
{}

void CRenderable::SShaderSetup::unload()
{
	Loaded = false;
	LoadedAttributes.clear();
	LoadedUniforms.clear();
}
