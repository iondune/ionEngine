
#include "CSceneNode.h"



CSceneNode::CSceneNode(ISceneNode * Parent)
: ISceneNode(Parent)
{}

void CSceneNode::Update()
{
	for (auto it : Components)
		it.second->Update(this);

	ISceneNode::Update();
}

void CSceneNode::Draw(IGraphicsEngine * Engine)
{
	for (auto it : Components)
		it.second->Draw(this, Engine);
	
	ISceneNode::Draw(Engine);
}
