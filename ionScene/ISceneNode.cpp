
#include "ISceneNode.h"


ISceneNode::ISceneNode(ISceneNode * Parent)
{
	this->Visible = true;
	this->TransformationDirty = false;
	this->Scale = 1.f;

	SetParent(Parent);
}

ISceneNode::~ISceneNode()
{}

bool ISceneNode::IsVisible() const
{
	return Visible;
}

void ISceneNode::SetVisible(bool const isVisible)
{
	Visible = isVisible;
}
