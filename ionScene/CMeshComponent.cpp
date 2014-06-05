
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
	
void CMeshComponent::Update(CSceneNode * Node)
{}

void RecurseAndDraw(CMeshComponent * Component, CGLGraphicsEngine * GLEngine, vector<CGLGraphicsEngine::SDrawDefinition> & Definitions, SMeshNode * Node,
	glm::mat4 Transformation, vector<ion::GL::ImageTexture *> const & Textures)
{
	Transformation = Transformation * Node->Transformation;

	for (uint i = 0; i < Node->Buffers.size(); ++ i)
	{
		CGLGraphicsEngine::SDrawDefinition Definition{Node->Buffers[i]->ArrayObject};
		Component->Model->Value = Transformation;
		Definition.AddUniform("Model", Component->Model);

		for (uint i = 0; i < Textures.size(); ++ i)
		{
			std::stringstream Label;
			Label << "Texture";
			Label << i;
			Definition.AddUniform(Label.str(), Component->TextureUniforms[i]);
			Definition.Textures.push_back(Textures[i]);
		}

		Definitions.push_back(Definition);
	}
	
	for (auto & Child : Node->GetChildren())
	{
		RecurseAndDraw(Component, GLEngine, Definitions, Child, Transformation, Textures);
	}
}

void CMeshComponent::Draw(CSceneNode * Node, IGraphicsEngine * Engine)
{
	if (InstanceOf<CGLGraphicsEngine>(Engine))
	{
		CGLGraphicsEngine * GLEngine = As<CGLGraphicsEngine>(Engine);
		RecurseAndDraw(this, GLEngine, GLEngine->RenderPasses[0].Elements[Shader], Mesh->Root, Node->GetAbsoluteTransformation(), Textures);
	}
}
