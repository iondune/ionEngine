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

void CScene::enableDebugData(EDebugData::Domain const type)
{
	if (type == EDebugData::All)
		DebugDataFlags = -1;
	else
		DebugDataFlags |= type;
}

void CScene::disableDebugData(EDebugData::Domain const type)
{
	if (type == EDebugData::All)
		DebugDataFlags = 0;
	else
		DebugDataFlags &= ~type;
}
