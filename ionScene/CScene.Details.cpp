#include "CScene.h"


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
