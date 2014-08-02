#include "CRenderable.h"


void CRenderable::addAttribute(std::string const & label, sharedPtr<IAttribute const> const attribute)
{
	Attributes[label] = attribute;
}

void CRenderable::addUniform(std::string const & label, sharedPtr<IUniform const> const uniform)
{
	Uniforms[label] = uniform;
}

void CRenderable::removeAttribute(std::string const & label)
{
	std::map<std::string, sharedPtr<IAttribute const> >::iterator it = Attributes.find(label);

	if (it != Attributes.end())
		Attributes.erase(it);
}

void CRenderable::removeUniform(std::string const & label)
{
	std::map<std::string, sharedPtr<IUniform const> >::iterator it = Uniforms.find(label);

	if (it != Uniforms.end())
		Uniforms.erase(it);
}

sharedPtr<IAttribute const> const CRenderable::getAttribute(std::string const & label)
{
	std::map<std::string, sharedPtr<IAttribute const> >::iterator it = Attributes.find(label);
	if (it != Attributes.end())
		return it->second;

	return sharedPtr<IAttribute const>();
}

sharedPtr<IUniform const> const CRenderable::getUniform(std::string const & label)
{
	if (label == "uModelMatrix")
		return BindUniform(ModelMatrix);

	if (label == "uNormalMatrix")
		return BindUniform(NormalMatrix);

	if (label == "uMaterial.AmbientColor")
		return BindUniform(Material.AmbientColor);

	if (label == "uMaterial.DiffuseColor")
		return BindUniform(Material.DiffuseColor);

	if (label == "uMaterial.SpecularColor")
		return BindUniform(Material.SpecularColor);

	if (label == "uMaterial.Shininess")
		return BindUniform(Material.Shininess);

	std::map<std::string, sharedPtr<IUniform const> >::iterator it = Uniforms.find(label);
	if (it != Uniforms.end())
		return it->second;

	return sharedPtr<IUniform const>();
}
