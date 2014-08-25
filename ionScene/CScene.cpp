
#include "CScene.h"


CScene::CScene()
{}

ICamera * const CScene::GetActiveCamera()
{
	return ActiveCamera;
}

ICamera const * const CScene::GetActiveCamera() const
{
	return ActiveCamera;
}

void CScene::SetActiveCamera(ICamera * const activeCamera)
{
	ActiveCamera = activeCamera;
}

void CScene::DrawAll(CDrawManager * DrawManager)
{
	Root->Update();
	DrawManager->Draw(this);
}

ISceneNode * CScene::GetRoot()
{
	return Root;
}
