
#include <ionWindow.h>
#include <ionGL.h>

using namespace ion::GL;


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	//////////////////
	// Buffer Setup //
	//////////////////

	vector<f32> const Vertices{
		0.0f,  0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	vector<u32> const Indices{
		0, 1, 2
	};

	VertexBuffer * vbo = new VertexBuffer;
	vbo->Data(Vertices, 2);

	IndexBuffer * ibo = new IndexBuffer;
	ibo->Data(Indices);

	
	//////////////////
	// Shader Setup //
	//////////////////

	string const VertexShaderSource = R"SHADER(
		#version 150
		in vec2 position;
		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
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

	VertexShader * vert = new VertexShader;
	vert->Source(VertexShaderSource);
	if (! vert->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << vert->InfoLog() << std::endl;

	FragmentShader * frag = new FragmentShader;
	frag->Source(FragmentShaderSource);
	if (! frag->Compile())
		std::cerr << "Failed to compile vertex shader!" << std::endl << frag->InfoLog() << std::endl;

	Program * shader = new Program;
	shader->AttachShader(vert);
	shader->AttachShader(frag);
	shader->Link();


	///////////////
	// Draw Loop //
	///////////////

	DrawConfig * Config = new DrawConfig{shader};
	Config->AddVertexBuffer("position", vbo);
	Config->SetIndexBuffer(ibo);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Context::Clear({ EBuffer::Color, EBuffer::Depth });

		DrawContext Context{shader};
		Context.Draw(Config);

		Window->SwapBuffers();
	}


	/////////////
	// Cleanup //
	/////////////

	delete Config;

	delete shader;
	delete ibo;
	delete vbo;

	return 0;
}
