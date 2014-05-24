
#pragma once

#include <ionCore.h>

#include "CSceneNode.h"


class CSceneManager;

class CSceneNodeFactory
{

public:

	CSceneNodeFactory(CSceneManager * SceneManager);

	CSceneNode * AddMeshNode(string const & Mesh, string const & Shader);

private:

	CSceneManager * SceneManager;

};
