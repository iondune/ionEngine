
#include "CSceneManager.h"


ICamera * const CSceneManager::GetActiveCamera()
{
	return ActiveCamera;
}

ICamera const * const CSceneManager::GetActiveCamera() const
{
	return ActiveCamera;
}

void CSceneManager::SetActiveCamera(ICamera * const activeCamera)
{
	ActiveCamera = activeCamera;
}

void CSceneManager::DrawAll(IGraphicsEngine * Engine)
{
	Engine->Begin();
	Root->Draw(Engine);
	Engine->Finalize();
}

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

ISceneNode * CSceneManager::GetRoot()
{
	return Root;
}

CSceneManager::CSceneManager()
{}
