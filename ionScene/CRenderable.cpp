#include "CRenderable.h"


// STL
#include <iostream>

// Core
#include <glm/gtc/matrix_transform.hpp>

// Scene
#include "SUniform.h"



CRenderable::SMaterial::SMaterial()
{
	loadDefaults();
}

void CRenderable::SMaterial::loadDefaults()
{
	Shininess = 1000.0f;
	AmbientColor = SColor(0.15f, 0.15f, 0.15f);
	DiffuseColor = SColor(0.8f, 0.8f, 0.8f);
}

void CRenderable::SMaterial::setTexture(unsigned int const Layer, CTexture * const Texture)
{
	if (Layer >= Textures.size())
		Textures.resize(Layer + 1, 0);
	Textures[Layer] = Texture;

	// TO DO : Cull Nulls from the end
}

CRenderable::SShaderContext::SShaderContext()
	: Loaded(false)
{}

void CRenderable::SShaderContext::unload()
{
	Loaded = false;
	LoadedAttributes.clear();
	LoadedUniforms.clear();
}

CRenderable::CRenderable(CSceneObject * parent)
	: DrawElementType(EDrawElementType::Triangles), NormalObject(0), IndexBufferObject(0), ParentObject(parent), ElementCount(0)
{}

CRenderable::SMaterial const & CRenderable::getMaterial() const
{
	return Material;
}

void CRenderable::setMaterial(CRenderable::SMaterial const & material)
{
	Material = material;
}

void CRenderable::setTexture(unsigned int const Layer, CTexture * const Texture)
{
	Material.setTexture(Layer, Texture);
}

EDrawElementType const CRenderable::getDrawType() const
{
	return DrawElementType;
}

void CRenderable::setDrawType(EDrawElementType const drawType)
{
	DrawElementType = drawType;
}

CBufferObject<GLushort> * CRenderable::getIndexBufferObject()
{
	return IndexBufferObject;
}

void CRenderable::setIndexBufferObject(CBufferObject<GLushort> * indexBufferObject)
{
	IndexBufferObject = indexBufferObject;
}

void CRenderable::addAttribute(std::string const & label, boost::shared_ptr<IAttribute const> const attribute)
{
	Attributes[label] = attribute;
}

void CRenderable::addUniform(std::string const & label, boost::shared_ptr<IUniform const> const uniform)
{
	Uniforms[label] = uniform;
}

void CRenderable::removeAttribute(std::string const & label)
{
	std::map<std::string, boost::shared_ptr<IAttribute const> >::iterator it = Attributes.find(label);

	if (it != Attributes.end())
		Attributes.erase(it);
}

void CRenderable::removeUniform(std::string const & label)
{
	std::map<std::string, boost::shared_ptr<IUniform const> >::iterator it = Uniforms.find(label);

	if (it != Uniforms.end())
		Uniforms.erase(it);
}

boost::shared_ptr<IAttribute const> const CRenderable::getAttribute(std::string const & label)
{
	std::map<std::string, boost::shared_ptr<IAttribute const> >::iterator it = Attributes.find(label);
	if (it != Attributes.end())
		return it->second;

	return boost::shared_ptr<IAttribute const>();
}

boost::shared_ptr<IUniform const> const CRenderable::getUniform(std::string const & label)
{
	if (label == "uModelMatrix")
		return BindUniform(ModelMatrix);

	if (label == "uNormalMatrix")
		return BindUniform(NormalMatrix);

	if (label == "uMaterial.AmbientColor")
		return BindUniform(Material.AmbientColor);

	if (label == "uMaterial.DiffuseColor")
		return BindUniform(Material.DiffuseColor);

	if (label == "uMaterial.Shininess")
		return BindUniform(Material.Shininess);

	std::map<std::string, boost::shared_ptr<IUniform const> >::iterator it = Uniforms.find(label);
	if (it != Uniforms.end())
		return it->second;

	return boost::shared_ptr<IUniform const>();
}

CRenderable * & CRenderable::getDebuggingNormalObject()
{
	return NormalObject;
}
