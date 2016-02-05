
#include "ISceneNode.h"


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

STransformation3 const & ISceneNode::GetTransformation() const
{
	return Transformation;
}

void ISceneNode::SetTransformation(glm::mat4 const & transformation)
{
	ExplicitTransformation = transformation;
	UseExplicitTransformation = true;
}

void ISceneNode::SetTranslation(SVector3f const & translation)
{
	Translation = translation;
	Transformation.SetTranslation(translation);
	UseExplicitTransformation = false;
}

void ISceneNode::SetPosition(vec3f const & translation)
{
	SetTranslation(translation);
	UseExplicitTransformation = false;
}

void ISceneNode::SetRotation(vec3f const & rotation)
{
	Rotation = rotation;
	Transformation.SetRotation(rotation);
	UseExplicitTransformation = false;
}

void ISceneNode::SetRotation(glm::mat4 const & matrix)
{
	Transformation.SetRotation(matrix);
	UseExplicitTransformation = false;
}

void ISceneNode::SetScale(vec3f const & scale)
{
	Scale = scale;
	Transformation.SetScale(scale);
	UseExplicitTransformation = false;
}

vec3f const & ISceneNode::GetRotation() const
{
	return Rotation;
}

vec3f const & ISceneNode::GetTranslation() const
{
	return Translation;
}

vec3f const & ISceneNode::GetPosition() const
{
	return Translation;
}

vec3f const & ISceneNode::GetScale() const
{
	return Scale;
}
