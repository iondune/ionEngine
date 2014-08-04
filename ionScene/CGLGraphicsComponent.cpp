
#include "CGLGraphicsComponent.h"


CGLGraphicsComponent::CGLGraphicsComponent()
{
}

void CGLGraphicsComponent::Update(CSceneNode * Node)
{
}

map<CShader *, vector<CDrawConfig *>> & CGLGraphicsComponent::GetDrawConfigurations()
{
	return DrawConfigurations;
}

map<CShader *, vector<CDrawConfig *>> const & CGLGraphicsComponent::GetDrawConfigurations() const
{
	return DrawConfigurations;
}
