
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
		ion::GL::UniformValue<glm::mat4> * View, * Projection;

		CGLGraphicsEngine::SDrawDefinition Definition{Mesh->Root->Buffers[0]->ArrayObject};
		Definition.AddUniform("Model", new ion::GL::UniformValue<glm::mat4>());
		Definition.AddUniform("View", View = new ion::GL::UniformValue<glm::mat4>());
		Definition.AddUniform("Projection", Projection = new ion::GL::UniformValue<glm::mat4>());
		GLEngine->RenderPasses[0].Elements[Shader].push_back(Definition);

		View->Value = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		Projection->Value = glm::perspective(60.0f, 1.333f, 0.1f, 20.f);
	}
}
