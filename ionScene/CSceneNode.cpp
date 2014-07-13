
#include "CSceneNode.h"



CSceneNode::CSceneNode(CScene * Scene, ISceneNode * Parent)
: ISceneNode(Parent)
{
	this->Scene = Scene;
	TransformationUniform.Value = & AbsoluteTransformation;
}

void CSceneNode::Update()
{
	for (auto it : Components)
		it.second->Update(this);

	ISceneNode::Update();
}

void CSceneNode::Draw(IGraphicsEngine * Engine)
{
	if (Visible)
		Engine->Draw(this);
	
	ISceneNode::Draw(Engine);
}

CScene * CSceneNode::GetScene()
{
	return Scene;
}

CUniformReference<glm::mat4> & CSceneNode::GetTransformationUniform()
{
	return TransformationUniform;
}
