
#include "ISceneNode.h"


void ISceneNode::CheckAbsoluteTransformation()
{
	// Absolute Transformations are recalculated top-down
	// A dirty transformation triggers a rebuild down all children

	if (TransformationDirty)
		UpdateAbsoluteTransformation();
	else
		RecurseOnChildren(& ISceneNode::CheckAbsoluteTransformation);
}

void ISceneNode::UpdateAbsoluteTransformation()
{
	AbsoluteTransformation = Transformation;

	if (Parent)
		AbsoluteTransformation = Parent->AbsoluteTransformation* AbsoluteTransformation;
	
	RecurseOnChildren(& ISceneNode::UpdateAbsoluteTransformation);
}

bool ISceneNode::CheckAbsoluteBoundingBox()
{
	// Absolute Bounding Boxes are recalculate bottom-up
	// A dirty bounding box triggers a rebuild all the way up

	bool RebuildNecessary = false;
	
	for (auto Child : Children)
		RebuildNecessary |= Child->CheckAbsoluteBoundingBox();

	if (RebuildNecessary)
		UpdateAbsoluteBoundingBox();

	return RebuildNecessary;
}

void ISceneNode::UpdateAbsoluteBoundingBox()
{
	AbsoluteBoundingBox = BoundingBox;
	
	for (auto Child : Children)
		AbsoluteBoundingBox.AddInternalBox(Child->GetAbsoluteBoundingBox());
}

void ISceneNode::Update()
{
	for (auto Child : Children)
		Child->Update();
}
