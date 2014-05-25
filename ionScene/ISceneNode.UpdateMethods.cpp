
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

void ISceneNode::Update()
{
	RecurseOnChildren(& ISceneNode::Update);
}

void ISceneNode::Draw(IGraphicsEngine * Engine)
{
	RecurseOnChildren(& ISceneNode::Draw, Engine);
}
