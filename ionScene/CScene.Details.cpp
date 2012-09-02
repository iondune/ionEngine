#include "CScene.h"


void CScene::addSceneObject(ISceneObject * sceneObject)
{
	RootObject.addChild(sceneObject);
}

void CScene::removeSceneObject(ISceneObject * sceneObject)
{
	RootObject.removeChild(sceneObject);
}

void CScene::removeAllSceneObjects()
{
	RootObject.removeAllChildren();
}

bool const CScene::isCullingEnabled() const
{
	return UseCulling;
}

void CScene::setCullingEnabled(bool const culling)
{
	UseCulling = culling;
}

bool const CScene::isDebugDataEnabled(EDebugData const type) const
{
	return RootObject.isDebugDataEnabled(type);
}

void CScene::enableDebugData(EDebugData::Domain const type)
{
	RootObject.enableDebugData(type);
}

void CScene::disableDebugData(EDebugData::Domain const type)
{
	RootObject.disableDebugData(type);
}
