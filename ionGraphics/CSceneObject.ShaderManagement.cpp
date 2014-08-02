#include "CSceneObject.h"

#include "CShaderLoader.h"


CShader const * const CSceneObject::getShader(sharedPtr<IRenderPass> Pass) const
{
	auto it = Shaders.find(Pass);
	if (it == Shaders.end())
		return 0;
	return it->second;
}

CShader * CSceneObject::getShader(sharedPtr<IRenderPass> Pass)
{
	auto it = Shaders.find(Pass);
	if (it == Shaders.end())
		return 0;
	return it->second;
}

void CSceneObject::setShader(sharedPtr<IRenderPass> Pass, CShader * shader)
{
	Shaders[Pass] = shader;
}

void CSceneObject::setShader(sharedPtr<IRenderPass> Pass, std::string const & shader)
{
	Shaders[Pass] = CShaderLoader::loadShader(shader);
}
