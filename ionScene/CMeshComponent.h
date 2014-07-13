
#pragma once

#include "CSceneNode.h"


class CMeshComponent : public ISceneNodeComponent
{

public:

	CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader, ion::GL::ImageTexture * Texture0 = 0);
	
	void Update(CSceneNode * Node);
	void Draw(CSceneNode * Node, IGraphicsEngine * Engine);

	CMesh * GetMesh();
	ion::GL::Program * GetShader();
	ion::GL::UniformValue<glm::mat4> * GetModel();
	uint GetTextureCount() const;
	ion::GL::ImageTexture * GetTexture(uint const Index);
	vector<ion::GL::ImageTexture *> & GetTextures();
	vector<ion::GL::UniformValue<int> *> & GetTextureUniforms();

	void SetTexture(uint const Index, ion::GL::ImageTexture * Texture);

private:

	CMesh * Mesh = nullptr;
	ion::GL::Program * Shader = nullptr;
	ion::GL::UniformValue<glm::mat4> * Model = nullptr;

	vector<ion::GL::ImageTexture *> Textures;
	vector<ion::GL::UniformValue<int> *> TextureUniforms;

};
