
#pragma once

#include <ionCore.h>

#include "CSceneNode.h"
#include "CPerspectiveCamera.h"
#include "COrthogonalCamera.h"
#include "ILightSceneNode.h"


class CSceneManager;

class CSceneNodeFactory
{

public:

	CSceneNodeFactory(CSceneManager * SceneManager);
	
	CSceneNode * AddSceneNode();
	CSceneNode * AddSceneNode(string const & Shader);
	CSceneNode * AddMeshNode(string const & Mesh, string const & Shader);
	CSceneNode * AddSkySphereNode(string const & TextureLabel);
	CPerspectiveCamera * AddPerspectiveCamera(f32 const AspectRatio);
	COrthogonalCamera * AddOrthogonalCamera(rect2f const & Area);

	ILightSceneNode * AddLight(vec3f const & Position);

private:

	CSceneManager * SceneManager = nullptr;

};
