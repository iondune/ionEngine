
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
	Dirty = true;
}

CMesh * CMeshComponent::GetMesh()
{
	return Mesh;
}

void CMeshComponent::Update(CSceneNode * Node)
{}

bool CMeshComponent::IsDirty() const
{
	return Dirty;
}

void CMeshComponent::Clean()
{
	Dirty = false;
}
