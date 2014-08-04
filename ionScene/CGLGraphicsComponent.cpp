
#include "CGLGraphicsComponent.h"


CGLGraphicsComponent::CGLGraphicsComponent()
{
}

void CGLGraphicsComponent::Update(CSceneNode * Node)
{
}

void CGLGraphicsComponent::Reset()
{
	for (auto Pass : DrawConfigurations)
	{
		for (auto Config : Pass.second)
			delete Config;
		Pass.second.clear();
	}
}

map<CShader *, vector<CDrawConfig *>> & CGLGraphicsComponent::GetDrawConfigurations()
{
	return DrawConfigurations;
}

map<CShader *, vector<CDrawConfig *>> const & CGLGraphicsComponent::GetDrawConfigurations() const
{
	return DrawConfigurations;
}
