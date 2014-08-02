
#pragma once

#include <ionAsset.h>
#include "ISceneNodeComponent.h"


class CMeshComponent : public ISceneNodeComponent
{

public:
	
	CMeshComponent();
	CMeshComponent(CMesh * Mesh);
	
	void Update(CSceneNode * Node);

	void SetMesh(CMesh * Mesh);
	CMesh * GetMesh();

private:

	CMesh * Mesh = nullptr;

};
