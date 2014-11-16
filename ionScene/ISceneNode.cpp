
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

void ISceneNode::SetDebugName(string const & DebugName)
{
	this->DebugName = DebugName;
}

string const & ISceneNode::GetDebugName() const
{
	return DebugName;
}
