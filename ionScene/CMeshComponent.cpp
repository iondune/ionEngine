
#include "CMeshComponent.h"


CMeshComponent::CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader)
{
	this->Mesh = Mesh;
	this->Shader = Shader;
}
	
void CMeshComponent::Update(CSceneNode * Node)
{}

void CMeshComponent::Draw(CSceneNode * Node)
{}
