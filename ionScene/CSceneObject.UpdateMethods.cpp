#include "CSceneObject.h"

#include "SUniform.h"
#include "SAttribute.h"


void CSceneObject::load(IScene const * const Scene, sharedPtr<IRenderPass> Pass)
{
	ISceneObject::load(Scene, Pass);

	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->load(Scene, Pass);
}

void CSceneObject::unload()
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->unload();
}

void CSceneObject::unload(sharedPtr<IRenderPass> Pass)
{
	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->unload(Pass);
}

bool CSceneObject::draw(IScene const * const Scene, sharedPtr<IRenderPass> Pass, bool const CullingEnabled)
{
	if (! ISceneObject::draw(Scene, Pass, CullingEnabled))
		return false;

	Pass->onPreDrawObject(this);
	
	auto ShaderIterator = Shaders.find(Pass);

	if (ShaderIterator == Shaders.end())
	{
		// This message not needed, no defined shader means it should not draw, equivalent to {}
		//std::cerr << "Failed to draw object " << this << ", shader not defined for current Pass." << std::endl;
		return true;
	}

	CShader * Shader = ShaderIterator->second;

	if (! Shader)
		return true;

	CShaderContext ShaderContext(* Shader);

	// Not Used ?
	//for (std::map<std::pair<GLint, std::string>, sharedPtr<IAttribute const> >::iterator it = LoadedAttributes.begin(); it != LoadedAttributes.end(); ++ it)
	//	it->second->bind(it->first.first, ShaderContext);
	//for (std::map<std::pair<GLint, std::string>, sharedPtr<IUniform const> >::iterator it = LoadedUniforms.begin(); it != LoadedUniforms.end(); ++ it)
	//	it->second->bind(it->first.first, ShaderContext);

	for (std::vector<CRenderable *>::iterator it = Renderables.begin(); it != Renderables.end(); ++ it)
		(* it)->draw(Scene, Pass, ShaderContext);

	Pass->onPostDrawObject(this);

	return true;
}
