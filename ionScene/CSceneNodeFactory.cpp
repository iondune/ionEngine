
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

CSceneNode * CSceneNodeFactory::AddSkySphereNode(ion::GL::ImageTexture * Texture)
{
	string const VertexShaderSource = R"SHADER(
		#version 150
		in vec3 Position;
		in vec3 Normal;
		in vec2 TexCoord;

		uniform mat4 Model;
		uniform mat4 View;
		uniform mat4 Projection;

		out vec2 fTexCoord;

		void main()
		{
			vec4 Position = Projection * View * Model * vec4(Position, 1.0);
			gl_Position = Position.xyww;
			fTexCoord = TexCoord;
		}
	)SHADER";

	string const FragmentShaderSource = R"SHADER(
		#version 150
		in vec2 fTexCoord;

		uniform sampler2D Texture0;

		out vec4 outColor;

		void main()
		{
			outColor = texture(Texture0, fTexCoord);
		}
	)SHADER";

	ion::GL::Program * Shader = SceneManager->GetShaderLibrary()->LoadFromSource("Skybox", VertexShaderSource, FragmentShaderSource);
	CMesh * Mesh = CGeometryCreator::CreateSkySphere();

	CSceneNode * Node = new CSceneNode{SceneManager->GetScene(), SceneManager->GetRoot()};
	Node->AddComponent(new CMeshComponent{Mesh, Shader, Texture});
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
