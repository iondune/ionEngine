
#include "ISceneNode.h"


glm::mat4 const & ISceneNode::GetAbsoluteTransformation() const
{
	return AbsoluteTransformation;
}

STransformation3 const & ISceneNode::GetTransformation() const
{
	return Transformation;
}

STransformation3 & ISceneNode::GetTransformation()
{
	return Transformation;
}


void ISceneNode::SetTranslation(SVector3f const & translation)
{
	Translation = translation;
	Transformation.SetTranslation(translation);
	TransformationDirty = true;
}

void ISceneNode::SetTransformation(glm::mat4 const & transformation)
{
	ExplicitTransformation = transformation;
	UseExplicitTransformation = true;
}

void ISceneNode::SetPosition(SVector3f const & translation)
{
	SetTranslation(translation);
}

void ISceneNode::SetRotation(SVector3f const & rotation)
{
	Rotation = rotation;
	Transformation.SetRotation(rotation);
	TransformationDirty = true;
}

void ISceneNode::SetRotation(glm::mat4 const & matrix)
{
	Transformation.SetRotation(matrix);
	TransformationDirty = true;
}

void ISceneNode::SetScale(SVector3f const & scale)
{
	Scale = scale;
	Transformation.SetScale(scale);
	TransformationDirty = true;
}


SVector3f const & ISceneNode::GetRotation() const
{
	return Rotation;
}

SVector3f const & ISceneNode::GetTranslation() const
{
	return Translation;
}

SVector3f const & ISceneNode::GetPosition() const
{
	return Translation;
}

SVector3f const & ISceneNode::GetScale() const
{
	return Scale;
}
