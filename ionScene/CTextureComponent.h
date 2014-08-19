
#pragma once

#include "CSceneNode.h"


class CTextureComponent : public ISceneNodeComponent
{

public:

	CTextureComponent(CTexture * Texture0 = 0);
	
	void Update(CSceneNode * Node);

	uint GetTextureCount() const;

	CTexture * GetTexture(uint const Index);
	ion::GL::UniformValue<int> * GetTextureUniform(uint const Index);

	vector<CTexture *> & GetTextures();
	vector<ion::GL::UniformValue<int> *> & GetTextureUniforms();

	void SetTexture(uint const Index, CTexture * Texture);

	bool IsDirty() const;
	void SetClean();

private:

	vector<CTexture *> Textures;
	vector<ion::GL::UniformValue<int> *> TextureUniforms;

	bool Dirty = false;

};
