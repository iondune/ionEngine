
#include "CSceneNodeFactory.h"
#include "CSceneManager.h"
#include "CMeshComponent.h"


CSceneNodeFactory::CSceneNodeFactory(CSceneManager * SceneManager)
{
	this->SceneManager = SceneManager;
}

CSceneNode * CSceneNodeFactory::AddMeshNode(string const & MeshLabel, string const & ShaderLabel)
{
	CSceneNode * Node = 0;
	CMesh * Mesh = SceneManager->GetMeshLibrary()->Get(MeshLabel);
	ion::GL::Program * Shader = SceneManager->GetShaderLibrary()->Get(ShaderLabel);

	if (Mesh && Shader)
	{
		Node = new CSceneNode{SceneManager->GetRoot()};
		Node->AddComponent(new CMeshComponent{Mesh, Shader});
	}

	return Node;
}

CPerspectiveCamera * CSceneNodeFactory::AddPerspectiveCamera(f32 const AspectRatio)
{
	return new CPerspectiveCamera{SceneManager->GetRoot(), AspectRatio};
}
