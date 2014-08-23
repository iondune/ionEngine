
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
