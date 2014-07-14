
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

CShader * CShaderComponent::GetShader()
{
	return Shader;
}

void CShaderComponent::Update(CSceneNode * Node)
{}
