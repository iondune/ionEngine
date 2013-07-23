#include "CScene.h"

#include "SAttribute.h"


CScene::CScene()
	: UseCulling(true)
{
	ActiveCamera = & DefaultCamera;

	addUniform("uProjMatrix", sharedNew(new SUniformReference<glm::mat4>(ProjMatrix)));
	addUniform("uViewMatrix", sharedNew(new SUniformReference<glm::mat4>(ViewMatrix)));
	addUniform("uLightCount", sharedNew(new SUniformReference<s32>(LightCount)));
	addUniform("uCameraPosition", sharedNew(new SUniformReference<vec3f>(CameraPosition)));

	RootObject.setCullingEnabled(false);
}
