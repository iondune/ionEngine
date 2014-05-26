
#pragma once

#include <ionCore.h>

#include "CSceneNode.h"
#include "CPerspectiveCamera.h"


class CSceneManager;

class CSceneNodeFactory
{

public:

	CSceneNodeFactory(CSceneManager * SceneManager);
	
	CSceneNode * AddMeshNode(string const & Mesh, string const & Shader);
	CPerspectiveCamera * AddPerspectiveCamera();

private:

	CSceneManager * SceneManager;

};
