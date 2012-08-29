#include "CScene.h"

#include <sstream>


CLightSceneObject const CScene::SLightBinding::NullLight = CLightSceneObject(color4f(0.f), 0.f);

CScene::SLightBinding::SLightBinding(CLightSceneObject const * const LightObject)
{
	bind(LightObject);
}

void CScene::SLightBinding::bind(CLightSceneObject const * const LightObject)
{
	ColorBind.Value = & LightObject->getColor();
	RadiusBind.Value = & LightObject->getRadius();
	PositionBind.Value = & LightObject->getTranslation();
}

CScene::CScene()
	: BindProjMatrix(ProjMatrix), BindViewMatrix(ViewMatrix), BindLightCount(LightCount), UseCulling(true)
{
	ActiveCamera = & DefaultCamera;

	addUniform("uProjMatrix", staticPtr<IUniform const>(& BindProjMatrix));
	addUniform("uViewMatrix", staticPtr<IUniform const>(& BindViewMatrix));
	addUniform("uLightCount", staticPtr<IUniform const>(& BindLightCount));

	RootObject.setCullingEnabled(false);
}

ICameraSceneObject * const CScene::getActiveCamera()
{
	return ActiveCamera;
}

ICameraSceneObject const * const CScene::getActiveCamera() const
{
	return ActiveCamera;
}

void CScene::setActiveCamera(ICameraSceneObject * const activeCamera)
{
	ActiveCamera = activeCamera;
}

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

bool const CScene::isCullingEnabled() const
{
	return UseCulling;
}

void CScene::setCullingEnabled(bool const culling)
{
	UseCulling = culling;
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

		if (remaining == "Color")
		{
			if (index >= Lights.size())
				return BindUniform(NullLight.Color);
			else
				return BindUniform(Lights[index]->Color);
		}
		else if (remaining == "Position")
		{
			if (index >= Lights.size())
				return BindUniform(NullLight.Position);
			else
				return BindUniform(Lights[index]->Position);
		}
		else if (remaining == "Radius")
		{
			if (index >= Lights.size())
				return BindUniform(NullLight.Radius);
			else
				return BindUniform(Lights[index]->Radius);
		}
	}

	auto it = Uniforms.find(label);

	if (it != Uniforms.end())
		return it->second;

	return smartPtr<IUniform const>();
}

void CScene::update()
{
	ActiveCamera->recalculateViewMatrix();
	ViewMatrix = ActiveCamera->getViewMatrix();
	ProjMatrix = ActiveCamera->getProjectionMatrix();

	if (LightCount != Lights.size())
	{
		SceneChanged = true;
		LightCount = Lights.size();
	}

	RootObject.updateAbsoluteTransformation();
	RootObject.update();
}

