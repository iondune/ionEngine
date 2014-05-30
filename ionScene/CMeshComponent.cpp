
#include "CMeshComponent.h"

#include "CGLGraphicsEngine.h"


CMeshComponent::CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader, ion::GL::ImageTexture * Texture0)
{
	this->Mesh = Mesh;
	this->Shader = Shader;

	if (Texture0)
		Textures.push_back(Texture0);
}
	
void CMeshComponent::Update(CSceneNode * Node)
{}

void CMeshComponent::Draw(CSceneNode * Node, IGraphicsEngine * Engine)
{
	if (InstanceOf<CGLGraphicsEngine>(Engine))
	{
		CGLGraphicsEngine * GLEngine = As<CGLGraphicsEngine>(Engine);
		CGLGraphicsEngine::SDrawDefinition Definition{Mesh->Root->Buffers[0]->ArrayObject};
		Definition.AddUniform("Model", new ion::GL::UniformValue<glm::mat4>(Node->GetAbsoluteTransformation()));

		for (uint i = 0; i < Textures.size(); ++ i)
		{
			std::stringstream Label;
			Label << "Texture";
			Label << i;
			Definition.AddUniform(Label.str(), new ion::GL::UniformValue<int>(i));
			Definition.Textures.push_back(Textures[i]);
		}

		GLEngine->RenderPasses[0].Elements[Shader].push_back(Definition);
	}
}
