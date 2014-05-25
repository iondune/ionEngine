
#pragma once

#include "CSceneNode.h"


class CMeshComponent : public CSceneNode::IComponent
{

public:

	CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader);
	
	void Update(CSceneNode * Node);
	void Draw(CSceneNode * Node, IGraphicsEngine * Engine);

private:

	CMesh * Mesh;
	ion::GL::Program * Shader;

};
