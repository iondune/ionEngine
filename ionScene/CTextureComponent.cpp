
#include "CTextureComponent.h"


CTextureComponent::CTextureComponent(ion::GL::ImageTexture * Texture0)
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

ion::GL::ImageTexture * CTextureComponent::GetTexture(uint const Index)
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

vector<ion::GL::ImageTexture *> & CTextureComponent::GetTextures()
{
	return Textures;
}

vector<ion::GL::UniformValue<int> *> & CTextureComponent::GetTextureUniforms()
{
	return TextureUniforms;
}

void CTextureComponent::SetTexture(uint const Index, ion::GL::ImageTexture * Texture)
{
	if (Index >= Textures.size())
	{
		Textures.resize(Index, nullptr);
		TextureUniforms.resize(Index, nullptr);
	}

	Textures[Index] = Texture;
	if (! TextureUniforms[Index])
		TextureUniforms[Index] = new ion::GL::UniformValue<int>(Index);
}

void CTextureComponent::Update(CSceneNode * Node)
{}
