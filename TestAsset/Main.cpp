
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
		in vec3 Normal;

		uniform mat4 Model;
		uniform mat4 View;
		uniform mat4 Projection;

		out vec3 Color;

		void main()
		{
			gl_Position = Projection * View * Model * vec4(Position, 1.0);
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

	CMesh * Mesh =
		CGeometryCreator::CreateSphere();
		//CGeometryCreator::CreateDisc(0.5, 1.5, 0.25, 32, 5);
		//CGeometryCreator::CreateCube();
		//CGeometryCreator::CreateCylinder(2.f, 1.f, 1.f, 32, 16);
	Mesh->UpdateBuffers();

	VertexShader * Vert = new VertexShader;
	Vert->Source(VertexShaderSource);
	if (! Vert->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << Vert->InfoLog() << std::endl;

	FragmentShader * Frag = new FragmentShader;
	Frag->Source(FragmentShaderSource);
	if (! Frag->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << Frag->InfoLog() << std::endl;

	UniformValue<glm::mat4> * Model = new UniformValue<glm::mat4>;
	UniformValue<glm::mat4> * View = new UniformValue<glm::mat4>;
	UniformValue<glm::mat4> * Projection = new UniformValue<glm::mat4>;

	View->Value = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	Projection->Value = glm::perspective(60.0f, 1.333f, 0.1f, 20.f);

	Program * Shader = new Program;
	Shader->AttachShader(Vert);
	Shader->AttachShader(Frag);
	Shader->Link();
	Shader->BindAttributeLocation(0, "Position");
	Shader->BindAttributeLocation(1, "Normal");

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Context::Clear({ EBuffer::Color, EBuffer::Depth });

		DrawContext context(Shader);
		context.BindUniform("Model", Model);
		context.BindUniform("View", View);
		context.BindUniform("Projection", Projection);
		context.SetVertexArray(Mesh->MeshBuffers[0]->ArrayObject);
		context.Draw();

		Model->Value = glm::rotate(Model->Value, 0.01f, glm::vec3(0, 1, 0.25));

		Window->SwapBuffers();
	}

	delete Shader;
	delete Mesh;

	return 0;
}
