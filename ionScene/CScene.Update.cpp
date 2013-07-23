#include "CScene.h"


void CScene::update()
{
	ActiveCamera->recalculateViewMatrix();
	ViewMatrix = ActiveCamera->getViewMatrix();
	ProjMatrix = ActiveCamera->getProjectionMatrix();

	RootObject.updateAbsoluteTransformation();
	RootObject.update();

	LightCount = getLightBindingCount();
	CameraPosition = getActiveCamera()->getPosition();
}

void CScene::load(sharedPtr<IRenderPass> const Pass)
{
	RootObject.load(this, Pass);
}

void CScene::draw(sharedPtr<IRenderPass> const Pass)
{
	RootObject.draw(this, Pass, UseCulling);
}
