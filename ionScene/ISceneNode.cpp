
#include "ISceneNode.h"


ISceneNode::ISceneNode()
	: Visible(true), TransformationDirty(false), Scale(1.f)
{}


//////////////////
// Bounding Box //
//////////////////

SBoundingBox3f const & ISceneNode::GetAbsoluteBoundingBox() const
{
	return AbsoluteBoundingBox;
}

SBoundingBox3f const & ISceneNode::GetBoundingBox() const
{
	return BoundingBox;
}

void ISceneNode::SetBoundingBox(SBoundingBox3f const & boundingBox)
{
	BoundingBox = boundingBox;
	BoundingBoxDirty = true;
}


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
