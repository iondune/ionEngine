#include "CSceneObject.h"


CSceneObject::CSceneObject()
{
	for (int i = 0; i < ERenderPass::Count; ++ i)
		Shaders[i] = 0;
}
