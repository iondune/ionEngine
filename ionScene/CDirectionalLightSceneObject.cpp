#include "CDirectionalLightSceneObject.h"

#include "CShaderLoader.h"
#include "CShaderContext.h"

#include "CSceneEffectManager.h"
//#include "CSceneManager.h"
//#include "CDeferredShadingManager.h"


CDirectionalLightSceneObject::CDirectionalLightSceneObject(SVector3f const direction, SColorAf const & color)
	: Color(color), Direction(direction)
{
	Shader = CShaderLoader::loadShader("Deferred/DirectionalLight");

	setCullingEnabled(false);
}

bool CDirectionalLightSceneObject::draw(IScene const * const scene, ERenderPass const Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(scene, Pass, CullingEnabled))
		return false;

	switch (Pass)
	{
	case ERenderPass::Default:
	case ERenderPass::DeferredColors:
	case ERenderPass::ModelSpaceNormals:
		break;

	case ERenderPass::DeferredLights:
		{
			if (! Shader)
				break;

			CSceneEffectManager::SPostProcessPass Pass;
			// TODO: find a way to manage this, perhaps by scene-managed uniforms?
			//Pass.Textures["uNormal"] = ((CDeferredShadingManager *) ((CSceneManager *)scene)->getEffectManager())->DeferredNormalOutput;
			Pass.SetTarget = false;
			Pass.Shader = Shader;

			Pass.begin();
			Pass.Context->uniform("uColor", Color);
			Pass.Context->uniform("uDirection", Direction);

			Pass.end();
			break;
		}
	}

	return true;
}

void CDirectionalLightSceneObject::load(IScene const * const Scene, ERenderPass const Pass)
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
