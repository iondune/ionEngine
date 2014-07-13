
#include "CMeshComponent.h"

#include "CGLGraphicsEngine.h"


CMeshComponent::CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader, ion::GL::ImageTexture * Texture0)
{
	this->Mesh = Mesh;
	this->Shader = Shader;

	if (Texture0)
	{
		Textures.push_back(Texture0);
		TextureUniforms.push_back(new ion::GL::UniformValue<int>(0));
	}
	
	Model = new ion::GL::UniformValue<glm::mat4>{};
}

CMesh * CMeshComponent::GetMesh()
{
	return Mesh;
}

ion::GL::Program * CMeshComponent::GetShader()
{
	return Shader;
}

ion::GL::UniformValue<glm::mat4> * CMeshComponent::GetModel()
{
	return Model;
}

uint CMeshComponent::GetTextureCount() const
{
	return Textures.size();
}

ion::GL::ImageTexture * CMeshComponent::GetTexture(uint const Index)
{
	if (Textures.size() >= Index)
		return Textures[Index];
	return 0;
}

vector<ion::GL::ImageTexture *> & CMeshComponent::GetTextures()
{
	return Textures;
}

vector<ion::GL::UniformValue<int> *> & CMeshComponent::GetTextureUniforms()
{
	return TextureUniforms;
}

void CMeshComponent::SetTexture(uint const Index, ion::GL::ImageTexture * Texture)
{
	Textures.push_back(Texture);
	TextureUniforms.push_back(new ion::GL::UniformValue<int>(0));
}

void CMeshComponent::Update(CSceneNode * Node)
{}
