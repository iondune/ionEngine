
#include "CSceneNode.h"


void CSceneNode::Update()
{
	for (auto it : Components)
		it.second->Update(this);

	ISceneNode::Update();
}

void CSceneNode::Draw()
{
	for (auto it : Components)
		it.second->Draw(this);
	
	ISceneNode::Draw();
}
