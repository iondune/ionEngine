#include "ISceneObject.h"


glm::mat4 const & ISceneObject::getAbsoluteTransformation() const
{
	return AbsoluteTransformation;
}

STransformation3 const & ISceneObject::getTransformation() const
{
	return Transformation;
}

STransformation3 & ISceneObject::getTransformation()
{
	return Transformation;
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
