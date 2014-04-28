
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>

using namespace ion::GL;


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", false);

	string const VertexShaderSource = R"SHADER(
		#version 150
		in vec3 Position;
		uniform mat4 Model;
		void main()
		{
			gl_Position = Model * vec4(Position, 1.0);
		}
	)SHADER";

	string const FragmentShaderSource = R"SHADER(
		#version 150
		out vec4 outColor;
		void main()
		{
			outColor = vec4(1.0, 1.0, 1.0, 1.0);
		}
	)SHADER";

	CMesh * Cube = CMeshLoader::CreateCubeMesh();
	Cube->UpdateBuffers();

	VertexShader * Vert = new VertexShader;
	Vert->Source(VertexShaderSource);
	if (! Vert->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << Vert->InfoLog() << std::endl;

	FragmentShader * Frag = new FragmentShader;
	Frag->Source(FragmentShaderSource);
	if (! Frag->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << Frag->InfoLog() << std::endl;

	UniformValue<glm::mat4> * Model = new UniformValue<glm::mat4>;

	Program * Shader = new Program;
	Shader->AttachShader(Vert);
	Shader->AttachShader(Frag);
	Shader->Link();
	Shader->BindAttributeLocation(0, "Position");

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Context::Clear({ EBuffer::Color, EBuffer::Depth });

		Shader->Use();
		Cube->MeshBuffers[0]->ArrayObject->Draw();
		Model->Bind(Shader->GetActiveUniforms().find("Model")->second);
		Program::End();

		Model->Value = glm::rotate(Model->Value, 0.01f, glm::vec3(0, 1, 0.25));

		Window->SwapBuffers();
	}

	delete Shader;
	delete Cube;

	return 0;
}
