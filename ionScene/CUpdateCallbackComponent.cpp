
#include "CUpdateCallbackComponent.h"


CUpdateCallbackComponent::CUpdateCallbackComponent(std::function<void(CSceneNode *)> const & Callback)
{
	this->Callback = Callback;
}
	
void CUpdateCallbackComponent::Update(CSceneNode * Node)
{
	Callback(Node);
}

void CUpdateCallbackComponent::Draw(CSceneNode * Node, CDrawManager * Engine)
{}
