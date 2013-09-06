#include "CSceneObject.h"

#include "CImageLoader.h"


void CSceneObject::setMaterial(CRenderable::SMaterial const & material)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->setMaterial(material);
}

void CSceneObject::setMaterial(CRenderable::SMaterial const & material, unsigned int const Renderable)
{
	CRenderable * Child = getRenderable(Renderable);
	if (Child)
		Child->setMaterial(material);
}

void CSceneObject::setMaterial(CRenderable::SMaterial const & material, CRenderable * const Renderable)
{
	Renderable->setMaterial(material);
}


void CSceneObject::setTexture(unsigned int const Layer, CTexture * Texture)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->setTexture(Layer, Texture);
}

void CSceneObject::setTexture(unsigned int const Layer, std::string const & texture)
{
	setTexture(Layer, CImageLoader::LoadTexture(texture));
}

void CSceneObject::setTexture(unsigned int const Layer, CTexture * Texture, unsigned int const renderable)
{
	if (Renderables.size() > renderable)
		Renderables[renderable]->setTexture(Layer, Texture);
}

void CSceneObject::setTexture(unsigned int const Layer, std::string const & texture, unsigned int const renderable)
{
	setTexture(Layer, CImageLoader::LoadTexture(texture), renderable);
}

void CSceneObject::setTexture(unsigned int const Layer, CTexture * Texture, CRenderable * const Renderable)
{
	Renderable->setTexture(Layer, Texture);
}

void CSceneObject::setTexture(unsigned int const Layer, std::string const & texture, CRenderable * const Renderable)
{
	setTexture(Layer, CImageLoader::LoadTexture(texture), Renderable);
}

void CSceneObject::addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->addAttribute(label, attribute);
}

void CSceneObject::addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute, unsigned int const renderable)
{
	Renderables[renderable]->addAttribute(label, attribute);
}

void CSceneObject::addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute, CRenderable * const Renderable)
{
	Renderable->addAttribute(label, attribute);
}

void CSceneObject::addUniform(std::string const & label, sharedPtr<IUniform const> const uniform)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->addUniform(label, uniform);
}

void CSceneObject::addUniform(std::string const & label, sharedPtr<IUniform const> const uniform, unsigned int const renderable)
{
	Renderables[renderable]->addUniform(label, uniform);
}

void CSceneObject::addUniform(std::string const & label, sharedPtr<IUniform const> const uniform, CRenderable * const Renderable)
{
	Renderable->addUniform(label, uniform);
}
	
sharedPtr<IAttribute const> CSceneObject::getAttribute(std::string const & label)
{
	std::map<std::string, sharedPtr<IAttribute const> >::iterator it = Attributes.find(label);
	if (it != Attributes.end())
		return it->second;

	return sharedPtr<IAttribute const>();
}

sharedPtr<IUniform const> CSceneObject::getUniform(std::string const & label)
{
	std::map<std::string, sharedPtr<IUniform const> >::iterator it = Uniforms.find(label);
	if (it != Uniforms.end())
		return it->second;

	return sharedPtr<IUniform const>();
}

void CSceneObject::removeAttribute(std::string const & label)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->removeAttribute(label);
}

void CSceneObject::removeAttribute(std::string const & label, unsigned int const renderable)
{
	if (Renderables.size() > renderable)
		Renderables[renderable]->removeAttribute(label);
}

void CSceneObject::removeAttribute(std::string const & label, CRenderable * const Renderable)
{
	Renderable->removeAttribute(label);
}

void CSceneObject::removeUniform(std::string const & label)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->removeUniform(label);
}

void CSceneObject::removeUniform(std::string const & label, unsigned int const renderable)
{
	if (Renderables.size() > renderable)
		Renderables[renderable]->removeUniform(label);
}

void CSceneObject::removeUniform(std::string const & label, CRenderable * const Renderable)
{
	Renderable->removeUniform(label);
}
