
#pragma once

#include "CSceneNode.h"


class CMeshComponent : public ISceneNodeComponent
{

public:

	CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader);
	
	void Update(CSceneNode * Node);

	CMesh * GetMesh();
	ion::GL::Program * GetShader();

private:

	CMesh * Mesh = nullptr;
	ion::GL::Program * Shader = nullptr;

};
