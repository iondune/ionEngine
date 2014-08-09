
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
	void SetUniform(string const & Label, IUniform * Uniform);

	CShader * GetShader();
	IUniform * GetUniform(string const & Label);
	map<string, IUniform *> & GetUniforms();

	bool IsDirty() const;
	void Clean();

private:

	CShader * Shader = nullptr;
	map<string, IUniform *> Uniforms;

	bool Dirty = false;

};
