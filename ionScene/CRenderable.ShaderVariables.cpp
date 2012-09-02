#include "CRenderable.h"


void CRenderable::addAttribute(std::string const & label, smartPtr<IAttribute const> const attribute)
{
	Attributes[label] = attribute;
}

void CRenderable::addUniform(std::string const & label, smartPtr<IUniform const> const uniform)
{
	Uniforms[label] = uniform;
}

void CRenderable::removeAttribute(std::string const & label)
{
	std::map<std::string, smartPtr<IAttribute const> >::iterator it = Attributes.find(label);

	if (it != Attributes.end())
		Attributes.erase(it);
}

void CRenderable::removeUniform(std::string const & label)
{
	std::map<std::string, smartPtr<IUniform const> >::iterator it = Uniforms.find(label);

	if (it != Uniforms.end())
		Uniforms.erase(it);
}

smartPtr<IAttribute const> const CRenderable::getAttribute(std::string const & label)
{
	std::map<std::string, smartPtr<IAttribute const> >::iterator it = Attributes.find(label);
	if (it != Attributes.end())
		return it->second;

	return smartPtr<IAttribute const>();
}

smartPtr<IUniform const> const CRenderable::getUniform(std::string const & label)
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

	std::map<std::string, smartPtr<IUniform const> >::iterator it = Uniforms.find(label);
	if (it != Uniforms.end())
		return it->second;

	return smartPtr<IUniform const>();
}
