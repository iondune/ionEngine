#include "CRenderable.h"


// STL
#include <iostream>

// Core
#include <glm/gtc/matrix_transform.hpp>

// Scene
#include "SUniform.h"


// Constructor //

CRenderable::CRenderable(CSceneObject * parent)
	: DrawElementType(EDrawElementType::Triangles), NormalObject(0), IndexBufferObject(0), ParentObject(parent), ElementCount(0)
{}


// Material //

CRenderable::SMaterial const & CRenderable::getMaterial() const
{
	return Material;
}

void CRenderable::setMaterial(CRenderable::SMaterial const & material)
{
	Material = material;
}

// Textures //

void CRenderable::setTexture(unsigned int const Layer, CTexture * const Texture)
{
	Material.setTexture(Layer, Texture);
}

// Index Buffer //

CBufferObject<GLushort> * CRenderable::getIndexBufferObject()
{
	return IndexBufferObject;
}

void CRenderable::setIndexBufferObject(CBufferObject<GLushort> * indexBufferObject)
{
	IndexBufferObject = indexBufferObject;
}

// Primitive Draw Type

EDrawElementType const CRenderable::getDrawType() const
{
	return DrawElementType;
}

void CRenderable::setDrawType(EDrawElementType const drawType)
{
	DrawElementType = drawType;
}

// Element Count //

u32 const CRenderable::getElementCount()
{
	return ElementCount;
}

void CRenderable::setElementCount(u32 const elementCount)
{
	ElementCount = elementCount;
}

// Transformation //

STransformation3 const & CRenderable::getTransformation() const
{
	return Transformation;
}

void CRenderable::setTranslation(SVector3f const & translation)
{
	Transformation.setTranslation(translation);
}

void CRenderable::setPosition(SVector3f const & translation)
{
	setTranslation(translation);
}

void CRenderable::setRotation(SVector3f const & rotation)
{
	Transformation.setRotation(rotation);
}

void CRenderable::setRotation(glm::mat4 const & matrix)
{
	Transformation.setRotation(matrix);
}

void CRenderable::setScale(SVector3f const & scale)
{
	Transformation.setScale(scale);
}

// Debug Info //

CRenderable * & CRenderable::getDebuggingNormalObject()
{
	return NormalObject;
}
