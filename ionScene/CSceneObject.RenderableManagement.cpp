#include "CSceneObject.h"


void CSceneObject::addRenderable(CRenderable * Renderable)
{
	Renderables.push_back(Renderable);
}

void CSceneObject::removeRenderable(CRenderable * Renderable)
{
	Renderables.erase(std::remove(Renderables.begin(), Renderables.end(), Renderable), Renderables.end());
}

void CSceneObject::removeRenderable(unsigned int const index)
{
	if (index < Renderables.size())
		Renderables.erase(Renderables.begin() + index);
}

unsigned int const CSceneObject::getRenderableCount()
{
	return Renderables.size();
}

CRenderable * const CSceneObject::getRenderable(unsigned int const index)
{
	if (index >= Renderables.size())
		return 0;

	return * (Renderables.begin() + index);
}

CRenderable const * const CSceneObject::getRenderable(unsigned int const index) const
{
	if (index >= Renderables.size())
		return 0;

	return * (Renderables.begin() + index);
}
