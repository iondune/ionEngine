
#include "CTextureComponent.h"


CTextureComponent::CTextureComponent(CTexture * Texture0)
{
	if (Texture0)
	{
		Textures.push_back(Texture0);
		TextureUniforms.push_back(new ion::GL::UniformValue<int>(0));
	}
}

uint CTextureComponent::GetTextureCount() const
{
	return Textures.size();
}

CTexture * CTextureComponent::GetTexture(uint const Index)
{
	if (Textures.size() >= Index)
		return Textures[Index];
	return 0;
}

ion::GL::UniformValue<int> * CTextureComponent::GetTextureUniform(uint const Index)
{
	if (TextureUniforms.size() >= Index)
		return TextureUniforms[Index];
	return 0;
}

vector<CTexture *> & CTextureComponent::GetTextures()
{
	return Textures;
}

vector<ion::GL::UniformValue<int> *> & CTextureComponent::GetTextureUniforms()
{
	return TextureUniforms;
}

void CTextureComponent::SetTexture(uint const Index, CTexture * Texture)
{
	if (Index >= Textures.size())
	{
		Textures.resize(Index + 1, nullptr);
		TextureUniforms.resize(Index + 1, nullptr);
	}

	Textures[Index] = Texture;
	if (! TextureUniforms[Index])
		TextureUniforms[Index] = new ion::GL::UniformValue<int>(Index);
}

void CTextureComponent::Update(CSceneNode * Node)
{}
