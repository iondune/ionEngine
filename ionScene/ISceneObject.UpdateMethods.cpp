#include "ISceneObject.h"

#include "IScene.h"


void ISceneObject::checkAbsoluteTransformation()
{
	// Absolute Transformations are recalculated top-down
	// A dirty transformation triggers a rebuild down all children

	if (TransformationDirty)
		updateAbsoluteTransformation();
	else
		for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
			(* it)->checkAbsoluteTransformation();
}

void ISceneObject::updateAbsoluteTransformation()
{
	AbsoluteTransformation = Transformation;

	if (Parent)
		AbsoluteTransformation = Parent->AbsoluteTransformation* AbsoluteTransformation;

	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->updateAbsoluteTransformation();
}

bool ISceneObject::checkAbsoluteBoundingBox()
{
	// Absolute Bounding Boxes are recalculate bottom-up
	// A dirty bounding box triggers a rebuild all the way up

	bool RebuildNecessary = false;
	
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		RebuildNecessary |= (* it)->checkAbsoluteBoundingBox();

	if (RebuildNecessary)
		updateAbsoluteBoundingBox();

	return RebuildNecessary;
}

void ISceneObject::updateAbsoluteBoundingBox()
{
	AbsoluteBoundingBox = BoundingBox;

	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		AbsoluteBoundingBox.addInternalBox((* it)->getAbsoluteBoundingBox());
}

void ISceneObject::update()
{
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->update();
}

void ISceneObject::load(IScene const * const Scene, smartPtr<IRenderPass> const Pass)
{
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->load(Scene, Pass);
}

bool ISceneObject::draw(IScene const * const Scene, smartPtr<IRenderPass> const Pass, bool const CullingEnabled)
{
	// Non-visible objects and all children are culled
	if (! Visible)
		return false;
	
	++ TotalObjects;

	// If culling is enabled both globally and locally, do an absolute culling check
	if (CullingEnabled && UseCulling && isCulled(Scene->getActiveCamera(), true))
	{
		++ ObjectsCulled;
		return false;
	}
	else
	{
		for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
			(* it)->draw(Scene, Pass, CullingEnabled);

		// Relative culling check (this object only)
		return (! CullingEnabled) || (! UseCulling) || ! isCulled(Scene->getActiveCamera(), false);
	}
}
