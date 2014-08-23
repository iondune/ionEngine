
#include "ILightSceneNode.h"


ILightSceneNode::ILightSceneNode(ISceneNode * Parent)
	: ISceneNode(Parent)
{}

map<CShader *, vector<CDrawConfig *>> ILightSceneNode::PrepareDrawConfigurations(CDrawManager * DrawManager, IRenderPass * Pass)
{
	map<CShader *, vector<CDrawConfig *>> Configurations;

	if (Visible)
		DrawManager->RegisterLight(this);

	return Configurations;
}

void ILightSceneNode::SetRadius(float const Radius)
{
	this->Radius = Radius;
}

void ILightSceneNode::SetColor(color3f const & Color)
{
	this->Color = Color;
}

float ILightSceneNode::GetRadius() const
{
	return Radius;
}

color3f ILightSceneNode::GetColor() const
{
	return Color;
}
