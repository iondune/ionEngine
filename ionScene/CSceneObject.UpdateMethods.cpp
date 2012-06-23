#include "CSceneObject.h"

#include "SUniform.h"
#include "SAttribute.h"


void CSceneObject::load(IScene const * const Scene, ERenderPass const Pass)
{
	ISceneObject::load(Scene, Pass);

	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->load(Scene, Pass);
}

bool CSceneObject::draw(IScene const * const Scene, ERenderPass const Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(Scene, Pass, CullingEnabled))
		return false;

	CShader * Shader = Shaders[Pass];

	if (! Shader)
		return false;

	CShaderContext ShaderContext(* Shader);

	for (std::map<std::pair<GLint, std::string>, boost::shared_ptr<IAttribute const> >::iterator it = LoadedAttributes.begin(); it != LoadedAttributes.end(); ++ it)
		it->second->bind(it->first.first, ShaderContext);
	for (std::map<std::pair<GLint, std::string>, boost::shared_ptr<IUniform const> >::iterator it = LoadedUniforms.begin(); it != LoadedUniforms.end(); ++ it)
		it->second->bind(it->first.first, ShaderContext);

	switch (Pass)
	{
	case ERenderPass::Default:
	case ERenderPass::DeferredColors:
	case ERenderPass::ModelSpaceNormals:
		for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
			(* it)->draw(Scene, Pass, ShaderContext);
		break;

	case ERenderPass::DeferredLights:
		break;
	}

	return true;
}
