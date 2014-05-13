
#if 0
#include "CScene.h"


ICameraSceneObject * const CScene::getActiveCamera()
{
	return ActiveCamera;
}

ICameraSceneObject const * const CScene::getActiveCamera() const
{
	return ActiveCamera;
}

void CScene::setActiveCamera(ICameraSceneObject * const activeCamera)
{
	ActiveCamera = activeCamera;
}
#endif
