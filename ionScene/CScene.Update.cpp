
#if 0
#include "CScene.h"


void CScene::update()
{
	ActiveCamera->RecalculateViewMatrix();
	ViewMatrix = ActiveCamera->GetViewMatrix();
	ProjMatrix = ActiveCamera->GetProjectionMatrix();

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
#endif
