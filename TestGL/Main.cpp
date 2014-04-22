
#include <ionWindow.h>
#include <ionGL.h>
#include <GL/glew.h>

using namespace ion::GL;


void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;
 
	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, & InfoLogLength);
 
	if (InfoLogLength > 0)
	{
		GLchar * InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, & CharsWritten, InfoLog);
		std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
		delete [] InfoLog;
	}
}

int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", false);

	char const * VertexShaderSource =
		"	#version 150			\n"
		"	in vec2 position;		\n"
		"	void main()			\n"
		"	{					\n"
		"		gl_Position = vec4(position, 0.0, 1.0);	\n"
		"	}					\n";

	char const * FragmentShaderSource =
		"	#version 150				\n"
		"	out vec4 outColor;			\n"
		"	void main()				\n"
		"	{						\n"
		"		outColor = vec4(1.0, 1.0, 1.0, 1.0);	\n"
		"	}						\n";

	GLfloat const Vertices[] = {
		0.0f,  0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint const Elements[] = {
		0, 1, 2
	};


	VertexBuffer * vbo = new VertexBuffer;
	vbo->Data(sizeof(Vertices), Vertices, 2);

	IndexBuffer * ibo = new IndexBuffer;
	ibo->Data(sizeof(Elements), Elements);

	VertexArray * vao = new VertexArray;
	vao->SetIndexBuffer(ibo);
	vao->BindAttribute(0, vbo);

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
	shader->BindAttributeLocation(0, "position");

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shader->Use();
		vao->Draw();
		Program::End();

		Window->SwapBuffers();
	}

	delete shader;

	delete ibo;
	delete vbo;
	delete vao;

	return 0;
}
