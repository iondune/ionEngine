#include "CScene.h"

#include <sstream>
#include "SAttribute.h"

void CScene::addUniform(std::string const & label, sharedPtr<IUniform const> const uniform)
{
	Uniforms[label] = uniform;
}

void CScene::removeUniform(std::string const & label)
{
	auto it = Uniforms.find(label);

	if (it != Uniforms.end())
		Uniforms.erase(it);
}
sharedPtr<IAttribute const> const CScene::getAttribute(std::string const & label) const
{
	return sharedPtr<IAttribute const>();
}

sharedPtr<IUniform const> const CScene::getUniform(std::string const & label) const
{
	if (label.substr(0, 8) == "uLights[")
	{
		std::stringstream ss(label.substr(8));
		unsigned int index;
		ss >> index;
		std::string remaining = ss.str();
		remaining = remaining.substr(2 + DigitCount(index));

		SLightBinding const & LightBinding = getLightBinding(index);

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

	return sharedPtr<IUniform const>();
}
