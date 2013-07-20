#include "CScene.h"


CLightSceneObject const CScene::SLightBinding::NullLight = CLightSceneObject(color3f(0.f), 0.f);

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
		ColorBind = smartNew(new SUniformReference<color3f>());
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

CScene::SLightBinding & CScene::getLightBinding(unsigned int const index)
{
	if (index >= LightBindings.size())
		LightBindings.resize(index + 1);
	return LightBindings[index];
}

CScene::SLightBinding const & CScene::getLightBinding(unsigned int const index) const
{
	if (index >= LightBindings.size())
		LightBindings.resize(index + 1);
	return LightBindings[index];
}

u32 const CScene::getLightBindingCount() const
{
	return LightBindings.size();
}
