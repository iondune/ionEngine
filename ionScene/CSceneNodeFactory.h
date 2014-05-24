
#pragma once

#include <ionCore.h>

#include "ISceneNode.h"


class CSceneManager;

class CSceneNodeFactory
{

public:

	CSceneNodeFactory(CSceneManager * Scene);

	ISceneNode * AddMeshNode(string const & Mesh, string const & Shader);

};
