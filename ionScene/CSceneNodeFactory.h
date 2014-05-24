
#pragma once

#include <ionCore.h>

#include "CMeshSceneNode.h"


class CSceneManager;

class CSceneNodeFactory
{

public:

	CSceneNodeFactory(CSceneManager * Scene);

	CMeshSceneNode * AddMeshNode(string const & Mesh, string const & Shader);

};
