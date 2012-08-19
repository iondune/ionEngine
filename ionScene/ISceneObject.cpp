#include "ISceneObject.h"


ISceneObject::ISceneObject()
	: DebugDataFlags(0), Visible(true), Parent(0), UseCulling(true), TransformationDirty(false),
	RenderCategory(ERenderCategory::Default)
{}

glm::mat4 const & ISceneObject::getAbsoluteTransformation() const
{
	return AbsoluteTransformation;
}

void ISceneObject::setTranslation(SVector3f const & translation)
{
	Translation = translation;
	Transformation.setTranslation(translation);

	TransformationDirty = true;
}

void ISceneObject::setPosition(SVector3f const & translation)
{
	setTranslation(translation);
}

void ISceneObject::setRotation(SVector3f const & rotation)
{
	Rotation = rotation;
	Transformation.setRotation(rotation);

	TransformationDirty = true;
}

void ISceneObject::setRotation(glm::mat4 const & matrix)
{
	Transformation.setRotation(matrix);

	TransformationDirty = true;
}

void ISceneObject::setScale(SVector3f const & scale)
{
	Scale = scale;
	Transformation.setScale(scale);

	TransformationDirty = true;
}

SBoundingBox3f const & ISceneObject::getBoundingBox() const
{
	return BoundingBox;
}

void ISceneObject::setBoundingBox(SBoundingBox3f const & boundingBox)
{
	BoundingBox = boundingBox;

	BoundingBoxDirty = true;
}

SBoundingBox3f const & ISceneObject::getAbsoluteBoundingBox() const
{
	return AbsoluteBoundingBox;
}

bool const ISceneObject::isDebugDataEnabled(EDebugData const type) const
{
	return (type & DebugDataFlags) != 0;
}

void ISceneObject::enableDebugData(EDebugData const type)
{
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->enableDebugData(type);

	if (type == EDebugData::All)
		DebugDataFlags = -1;
	else
		DebugDataFlags |= type;
}

void ISceneObject::disableDebugData(EDebugData const type)
{
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->disableDebugData(type);

	if (type == EDebugData::All)
		DebugDataFlags = 0;
	else
		DebugDataFlags &= ~type;
}

bool const ISceneObject::intersectsWithLine(SLine3f const & line) const
{
	return BoundingBox.intersectsWithLine(line);
}

bool const ISceneObject::isVisible() const
{
	return Visible;
}

void ISceneObject::setVisible(bool const isVisible)
{
	// TO DO: Non visible objects should not be a part of hiearchies, so this should trigger a rebuild
	Visible = isVisible;
}

STransformation3 const & ISceneObject::getTransformation() const
{
	return Transformation;
}

ISceneObject const * const ISceneObject::getParent() const
{
	return Parent;
}

std::list<ISceneObject *> const & ISceneObject::getChildren() const
{
	return Children;
}

void ISceneObject::removeChild(ISceneObject * child)
{
	Children.erase(std::remove(Children.begin(), Children.end(), child), Children.end());
	child->Parent = 0;
}

void ISceneObject::addChild(ISceneObject * child)
{
	Children.push_back(child);
	child->Parent = this;
}

void ISceneObject::setParent(ISceneObject * parent)
{
	if (Parent)
		Parent->removeChild(this);

	if (parent)
		parent->addChild(this);
}

void ISceneObject::removeChildren()
{
	Children.clear();
}

SVector3f const & ISceneObject::getRotation() const
{
	return Rotation;
}

SVector3f const & ISceneObject::getTranslation() const
{
	return Translation;
}

SVector3f const & ISceneObject::getPosition() const
{
	return Translation;
}

SVector3f const & ISceneObject::getScale() const
{
	return Scale;
}
