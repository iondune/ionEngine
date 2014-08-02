
#include "CShaderComponent.h"


CShaderComponent::CShaderComponent()
{}

CShaderComponent::CShaderComponent(CShader * Shader)
{
	this->Shader = Shader;
}

void CShaderComponent::SetShader(CShader * Shader)
{
	this->Shader = Shader;
}

void CShaderComponent::SetUniform(string const & Label, IUniform * Uniform)
{
	Uniforms[Label] = Uniform;
}

CShader * CShaderComponent::GetShader()
{
	return Shader;
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
