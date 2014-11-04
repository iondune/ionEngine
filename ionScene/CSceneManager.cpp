
#include "CSceneManager.h"


CMeshLibrary * CSceneManager::GetMeshLibrary()
{
	return MeshLibrary;
}

CShaderLibrary * CSceneManager::GetShaderLibrary()
{
	return ShaderLibrary;
}

CTextureLibrary * CSceneManager::GetTextureLibrary()
{
	return TextureLibrary;
}

CSceneNodeFactory * CSceneManager::GetFactory()
{
	return Factory;
}

CDrawManager * CSceneManager::GetDrawManager()
{
	return DrawManager;
}

CRenderPassManager * CSceneManager::GetRenderPassManager()
{
	return RenderPassManager;
}

void CSceneManager::DrawAll()
{
	Scene->DrawAll(DrawManager, RenderPassManager);
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
