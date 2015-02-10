
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
	if (UseExplicitTransformation)
		AbsoluteTransformation = ExplicitTransformation;
	else
		AbsoluteTransformation = Transformation;

	if (Parent)
		AbsoluteTransformation = Parent->AbsoluteTransformation* AbsoluteTransformation;
	
	RecurseOnChildren(& ISceneNode::UpdateAbsoluteTransformation);
}

void ISceneNode::Update()
{
	UpdateAbsoluteTransformation();
	RecurseOnChildren(& ISceneNode::Update);
}
 
map<CShader *, vector<CDrawConfig *>> ISceneNode::PrepareDrawConfigurations(CDrawManager * DrawManager, IRenderPass * Pass)
{
	map<CShader *, vector<CDrawConfig *>> Configurations;

	if (Visible)
	{
		for (auto Child : Children)
		{
			if (Child->Visible)
			{
				auto ChildConfigurations = Child->PrepareDrawConfigurations(DrawManager, Pass);
				for (auto Config : ChildConfigurations)
				{
					AddAtEnd(Configurations[Config.first], Config.second);
				}
			}
		}
	}

	return Configurations;
}
