
#pragma once

#include "CSceneNode.h"


class CTextureComponent : public ISceneNodeComponent
{

public:

	CTextureComponent(ion::GL::ImageTexture * Texture0 = 0);
	
	void Update(CSceneNode * Node);

	uint GetTextureCount() const;

	ion::GL::ImageTexture * GetTexture(uint const Index);
	ion::GL::UniformValue<int> * GetTextureUniform(uint const Index);

	vector<ion::GL::ImageTexture *> & GetTextures();
	vector<ion::GL::UniformValue<int> *> & GetTextureUniforms();

	void SetTexture(uint const Index, ion::GL::ImageTexture * Texture);

private:

	vector<ion::GL::ImageTexture *> Textures;
	vector<ion::GL::UniformValue<int> *> TextureUniforms;

};
