
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
	
	bool IsDirty() const;
	void SetClean();

private:

	CMesh * Mesh = nullptr;

	bool Dirty = false;

};
