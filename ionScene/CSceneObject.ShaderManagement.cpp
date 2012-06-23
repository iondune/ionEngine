#include "CSceneObject.h"

#include <CShaderLoader.h>


CShader const * const CSceneObject::getShader() const
{
	return Shaders[ERenderPass::Default];
}

CShader * CSceneObject::getShader()
{
	return Shaders[ERenderPass::Default];
}

CShader const * const CSceneObject::getShader(ERenderPass const Pass) const
{
	return Shaders[Pass];
}

CShader * CSceneObject::getShader(ERenderPass const Pass)
{
	return Shaders[Pass];
}

void CSceneObject::setShader(ERenderPass const Pass, CShader * shader)
{
	Shaders[Pass] = shader;
}

void CSceneObject::setShader(ERenderPass const Pass, std::string const & shader)
{
	Shaders[Pass] = CShaderLoader::loadShader(shader);
}
