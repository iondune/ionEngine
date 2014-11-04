
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

void CScene::DrawAll(CDrawManager * DrawManager, CRenderPassManager * RenderPassManager)
{
	Root->Update();
	DrawManager->Draw(this, RenderPassManager);
}

ISceneNode * CScene::GetRoot()
{
	return Root;
}
