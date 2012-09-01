#include "CScene.h"

#include <sstream>


void CScene::addUniform(std::string const & label, smartPtr<IUniform const> const uniform)
{
	Uniforms[label] = uniform;
}

void CScene::removeUniform(std::string const & label)
{
	auto it = Uniforms.find(label);

	if (it != Uniforms.end())
		Uniforms.erase(it);
}
smartPtr<IAttribute const> const CScene::getAttribute(std::string const & label) const
{
	return smartPtr<IAttribute const>();
}

smartPtr<IUniform const> const CScene::getUniform(std::string const & label) const
{
	if (label.substr(0, 8) == "uLights[")
	{
		std::stringstream ss(label.substr(8));
		unsigned int index;
		ss >> index;
		std::string remaining = ss.str();
		remaining = remaining.substr(2 + digitCount(index));

		if (index >= LightBindings.size())
		{
			LightBindings.resize(index + 1);
		}

		SLightBinding const & LightBinding = LightBindings[index];

		if (remaining == "Color")
		{
			return LightBinding.ColorBind;
		}
		else if (remaining == "Position")
		{
			return LightBinding.PositionBind;
		}
		else if (remaining == "Radius")
		{
			return LightBinding.RadiusBind;
		}
	}

	auto it = Uniforms.find(label);

	if (it != Uniforms.end())
		return it->second;

	return smartPtr<IUniform const>();
}
