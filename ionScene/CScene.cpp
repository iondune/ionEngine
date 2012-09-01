#include "CScene.h"

#include "SAttribute.h"


CScene::CScene()
	: BindProjMatrix(ProjMatrix), BindViewMatrix(ViewMatrix), BindLightCount(LightCount), UseCulling(true)
{
	ActiveCamera = & DefaultCamera;

	addUniform("uProjMatrix", staticPtr<IUniform const>(& BindProjMatrix));
	addUniform("uViewMatrix", staticPtr<IUniform const>(& BindViewMatrix));
	addUniform("uLightCount", staticPtr<IUniform const>(& BindLightCount));

	RootObject.setCullingEnabled(false);
}
