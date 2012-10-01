#include "CScene.h"

#include "SAttribute.h"


CScene::CScene()
	: UseCulling(true)
{
	ActiveCamera = & DefaultCamera;

	addUniform("uProjMatrix", smartNew(new SUniformReference<glm::mat4>(ProjMatrix)));
	addUniform("uViewMatrix", smartNew(new SUniformReference<glm::mat4>(ViewMatrix)));
	//addUniform("uLightCount", smartNew(new SUniformReference<s32>(LightCount)));

	RootObject.setCullingEnabled(false);
}
