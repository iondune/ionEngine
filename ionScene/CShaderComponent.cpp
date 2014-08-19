
#include "CShaderComponent.h"


CShaderComponent::CShaderComponent()
{}

CShaderComponent::CShaderComponent(CShader * Shader, IRenderPass * RenderPass)
{
	this->Shaders[DefaultForwardRenderPass] = Shader;
}

void CShaderComponent::SetShader(CShader * Shader, IRenderPass * RenderPass)
{
	this->Shaders[RenderPass] = Shader;
	Dirty = true;
}

void CShaderComponent::SetUniform(string const & Label, IUniform * Uniform)
{
	Uniforms[Label] = Uniform;
	Dirty = true;
}

CShader * CShaderComponent::GetShader(IRenderPass * RenderPass)
{
	return Shaders[RenderPass];
}

IUniform * CShaderComponent::GetUniform(string const & Label)
{
	return Uniforms[Label];
}

map<string, IUniform *> & CShaderComponent::GetUniforms()
{
	return Uniforms;
}

void CShaderComponent::Update(CSceneNode * Node)
{}

bool CShaderComponent::IsDirty() const
{
	return Dirty;
}

void CShaderComponent::SetClean()
{
	Dirty = false;
}
