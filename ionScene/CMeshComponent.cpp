
#include "CMeshComponent.h"

#include "CGLGraphicsEngine.h"


CMeshComponent::CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader)
{
	this->Mesh = Mesh;
	this->Shader = Shader;
}

CMesh * CMeshComponent::GetMesh()
{
	return Mesh;
}

ion::GL::Program * CMeshComponent::GetShader()
{
	return Shader;
}

void CMeshComponent::Update(CSceneNode * Node)
{}
