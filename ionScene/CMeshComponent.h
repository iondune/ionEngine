
#pragma once

#include "CSceneNode.h"
#include "CGLGraphicsEngine.h"


class CMeshComponent : public CSceneNode::IComponent
{

public:

	CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader, ion::GL::ImageTexture * Texture0 = 0);
	
	void Update(CSceneNode * Node);
	void Draw(CSceneNode * Node, IGraphicsEngine * Engine);

	void SetTexture(uint const Index, ion::GL::ImageTexture * Texture);

private:

	CMesh * Mesh = nullptr;
	ion::GL::Program * Shader = nullptr;
	vector<ion::GL::ImageTexture *> Textures;
	vector<ion::GL::UniformValue<int> *> TextureUniforms;
	ion::GL::UniformValue<glm::mat4> * Model = nullptr;

	friend void RecurseAndDraw(CMeshComponent * Component, CGLGraphicsEngine * GLEngine, vector<CGLGraphicsEngine::SDrawDefinition> & Definitions, SMeshNode * Node,
		glm::mat4 Transformation, vector<ion::GL::ImageTexture *> const & Textures);

};
