
#include "CMeshComponent.h"

#include "CGLGraphicsEngine.h"


CMeshComponent::CMeshComponent(CMesh * Mesh, ion::GL::Program * Shader)
{
	this->Mesh = Mesh;
	this->Shader = Shader;
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

		GLEngine->RenderPasses[0].Elements[Shader].push_back(Definition);
	}
}
