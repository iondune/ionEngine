
#pragma once

#include <ionAsset.h>
#include "IRenderPass.h"
#include "ISceneNodeComponent.h"


class CShaderComponent : public ISceneNodeComponent
{

public:
	
	CShaderComponent();
	CShaderComponent(CShader * Shader, IRenderPass * RenderPass = DefaultForwardRenderPass);

	void Update(CSceneNode * Node);
	
	void SetShader(CShader * Shader, IRenderPass * RenderPass = DefaultForwardRenderPass);
	void SetUniform(string const & Label, IUniform * Uniform);

	CShader * GetShader(IRenderPass * RenderPass = DefaultForwardRenderPass);
	IUniform * GetUniform(string const & Label);
	map<string, IUniform *> & GetUniforms();

	bool IsDirty() const;
	void SetClean();

private:

	map<IRenderPass *, CShader *> Shaders;
	map<string, IUniform *> Uniforms;

	bool Dirty = false;

};
