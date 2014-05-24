
#include "ISceneNode.h"


ISceneNode::ISceneNode()
	: Visible(true), TransformationDirty(false), Scale(1.f)
{}


////////////////
// Visibility //
////////////////

bool ISceneNode::IsVisible() const
{
	return Visible;
}

void ISceneNode::SetVisible(bool const isVisible)
{
	// TO DO: Non visible objects should not be a part of hiearchies, so this should trigger a rebuild
	Visible = isVisible;
}
