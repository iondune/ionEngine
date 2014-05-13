
#if 0
#include "CDirectionalLightSceneObject.h"

#include <ionGraphics/CShaderLoader.h>
#include <ionGraphics/CShaderContext.h>

#include "CSceneEffectManager.h"
//#include "CSceneManager.h"
//#include "CDeferredShadingManager.h"


CDirectionalLightSceneObject::CDirectionalLightSceneObject(SVector3f const direction, SColorAf const & color)
	: Color(color), Direction(direction)
{
	Shader = CShaderLoader::loadShader("Deferred/DirectionalLight");

	setCullingEnabled(false);
}

bool CDirectionalLightSceneObject::draw(IScene const * const scene, sharedPtr<IRenderPass> Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(scene, Pass, CullingEnabled))
		return false;

	//if (Pass != DeferredPass)
	//	return true;

	if (! Shader)
		return true;

	CSceneEffectManager::SPostProcessPass DrawPass;
	// TODO: find a way to manage this, perhaps by scene-managed uniforms?
	//Pass.Textures["uNormal"] = ((CDeferredShadingManager *) ((CSceneManager *)scene)->getEffectManager())->DeferredNormalOutput;
	DrawPass.SetTarget = false;
	DrawPass.Shader = Shader;

	DrawPass.begin();
	DrawPass.Context->uniform("uColor", Color);
	DrawPass.Context->uniform("uDirection", Direction);

	DrawPass.end();

	return true;
}

void CDirectionalLightSceneObject::load(IScene const * const Scene, sharedPtr<IRenderPass> Pass)
{
}

void CDirectionalLightSceneObject::setDirection(SVector3f const & direction)
{
	Direction = direction;
}

void CDirectionalLightSceneObject::setColor(SVector3f const & color)
{
	Color = color;
}
#endif
