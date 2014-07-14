
#pragma once

#include <ionAsset.h>
#include "ISceneNodeComponent.h"


class CShaderComponent : public ISceneNodeComponent
{

public:
	
	CShaderComponent();
	CShaderComponent(CShader * Shader);
	void Update(CSceneNode * Node);

	void SetShader(CShader * Shader);
	CShader * GetShader();

private:

	CShader * Shader = nullptr;

};
