
#include "CMeshComponent.h"


CMeshComponent::CMeshComponent()
{}

CMeshComponent::CMeshComponent(CMesh * Mesh)
{
	this->Mesh = Mesh;
}

void CMeshComponent::SetMesh(CMesh * Mesh)
{
	this->Mesh = Mesh;
}

CMesh * CMeshComponent::GetMesh()
{
	return Mesh;
}

void CMeshComponent::Update(CSceneNode * Node)
{}
