
#pragma once

#include <ionCore.h>

#include "IScene.h"
#include "CMeshSceneNode.h"


class CSceneNodeFactory
{

public:

	CSceneNodeFactory(IScene * Scene);

	CMeshSceneNode * AddMeshNode(string const & Mesh, string const & Shader);

};
