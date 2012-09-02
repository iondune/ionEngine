#include "CScene.h"


void CScene::update()
{
	ActiveCamera->recalculateViewMatrix();
	ViewMatrix = ActiveCamera->getViewMatrix();
	ProjMatrix = ActiveCamera->getProjectionMatrix();

	RootObject.updateAbsoluteTransformation();
	RootObject.update();
}

void CScene::load(smartPtr<IRenderPass> const Pass)
{
	RootObject.load(this, Pass);
}

void CScene::draw(smartPtr<IRenderPass> const Pass)
{
	RootObject.draw(this, Pass, UseCulling);
}
