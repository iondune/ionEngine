
#include "CGLGraphicsComponent.h"


CGLGraphicsComponent::CGLGraphicsComponent()
{
}

void CGLGraphicsComponent::Update(CSceneNode * Node)
{
}

map<CShader *, CDrawConfig *> & CGLGraphicsComponent::GetRenderPasses()
{
	return RenderPasses;
}

map<CShader *, CDrawConfig *> const & CGLGraphicsComponent::GetRenderPasses() const
{
	return RenderPasses;
}
