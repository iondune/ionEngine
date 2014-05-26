
#include "CSceneNodeFactory.h"
#include "CSceneManager.h"
#include "CMeshComponent.h"
#include "CUpdateCallbackComponent.h"


CSceneNodeFactory::CSceneNodeFactory(CSceneManager * SceneManager)
{
	this->SceneManager = SceneManager;
}

CSceneNode * CSceneNodeFactory::AddMeshNode(string const & MeshLabel, string const & ShaderLabel)
{
	CSceneNode * Node = 0;
	CMesh * Mesh = SceneManager->GetMeshLibrary()->Get(MeshLabel);
	ion::GL::Program * Shader = SceneManager->GetShaderLibrary()->Get(ShaderLabel);

	if (Mesh && Shader)
	{
		Node = new CSceneNode{SceneManager->GetScene(), SceneManager->GetRoot()};
		Node->AddComponent(new CMeshComponent{Mesh, Shader});
	}

	return Node;
}

CSceneNode * CSceneNodeFactory::AddSkySphereNode()
{
	string const VertexShaderSource = R"SHADER(
		#version 150
		in vec3 Position;
		in vec3 Normal;

		uniform mat4 Model;
		uniform mat4 View;
		uniform mat4 Projection;

		out vec3 Color;

		void main()
		{
			vec4 Position = Projection * View * Model * vec4(Position, 1.0);
			gl_Position = Position.xyww;
			Color = normalize(Normal) / 2.0 + vec3(0.5);
		}
	)SHADER";

	string const FragmentShaderSource = R"SHADER(
		#version 150
		in vec3 Color;

		out vec4 outColor;

		void main()
		{
			outColor = vec4(Color, 1.0);
		}
	)SHADER";

	ion::GL::Program * Shader = SceneManager->GetShaderLibrary()->LoadFromSource("Skybox", VertexShaderSource, FragmentShaderSource);
	CMesh * Mesh = CGeometryCreator::CreateSphere();

	CSceneNode * Node = new CSceneNode{SceneManager->GetScene(), SceneManager->GetRoot()};
	Node->AddComponent(new CMeshComponent{Mesh, Shader});
	Node->AddComponent(new CUpdateCallbackComponent{[](CSceneNode * Node)
	{
		Node->SetPosition(Node->GetScene()->GetActiveCamera()->GetPosition());
	}});

	return Node;
}

CPerspectiveCamera * CSceneNodeFactory::AddPerspectiveCamera(f32 const AspectRatio)
{
	return new CPerspectiveCamera{SceneManager->GetRoot(), AspectRatio};
}
