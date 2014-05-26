
#include "CSceneNode.h"



CSceneNode::CSceneNode(CScene * Scene, ISceneNode * Parent)
: ISceneNode(Parent)
{
	this->Scene = Scene;
}

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

CScene * CSceneNode::GetScene()
{
	return Scene;
}
