#include "CScene.h"

#include "SAttribute.h"
#include <sstream>


CLightSceneObject const CScene::SLightBinding::NullLight = CLightSceneObject(color4f(0.f), 0.f);

CScene::SLightBinding::SLightBinding()
{
	bind(& NullLight);
}

CScene::SLightBinding::SLightBinding(CLightSceneObject const * const LightObject)
{
	bind(LightObject);
}

void CScene::SLightBinding::bind(CLightSceneObject const * const LightObject)
{
	if (! LightObject)
		return unbind();
	
	if (! ColorBind)
		ColorBind = smartNew(new SUniformReference<color4f>());
	if (! RadiusBind)
		RadiusBind = smartNew(new SUniformReference<f32>());
	if (! PositionBind)
		PositionBind = smartNew(new SUniformReference<vec3f>());

	ColorBind->Value = & LightObject->getColor();
	RadiusBind->Value = & LightObject->getRadius();
	PositionBind->Value = & LightObject->getTranslation();
}

void CScene::SLightBinding::unbind()
{
	bind(& NullLight);
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

void CScene::update()
{
	ActiveCamera->recalculateViewMatrix();
	ViewMatrix = ActiveCamera->getViewMatrix();
	ProjMatrix = ActiveCamera->getProjectionMatrix();

	RootObject.updateAbsoluteTransformation();
	RootObject.update();
}

void CScene::load(smartPtr<IRenderPass> const Pass)
{
	RootObject.load(this, Pass);
}

void CScene::draw(smartPtr<IRenderPass> const Pass)
{
	RootObject.draw(this, Pass, UseCulling);
}

bool const CScene::isCullingEnabled() const
{
	return UseCulling;
}

void CScene::setCullingEnabled(bool const culling)
{
	UseCulling = culling;
}
