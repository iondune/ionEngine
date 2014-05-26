
#include "CSceneManager.h"



CMeshLibrary * CSceneManager::GetMeshLibrary()
{
	return MeshLibrary;
}

CShaderLibrary * CSceneManager::GetShaderLibrary()
{
	return ShaderLibrary;
}

CSceneNodeFactory * CSceneManager::GetFactory()
{
	return Factory;
}

void CSceneManager::DrawAll(IGraphicsEngine * Engine)
{
	Scene->DrawAll(Engine);
}

CScene * CSceneManager::GetScene()
{
	return Scene;
}

ISceneNode * CSceneManager::GetRoot()
{
	return Scene->GetRoot();
}

CSceneManager::CSceneManager()
{}
