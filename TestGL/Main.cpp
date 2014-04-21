
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

	VertexArray * vao = new VertexArray;

	VertexBuffer * vbo = new VertexBuffer;
	vbo->Data(sizeof(Vertices), Vertices, 2);

	IndexBuffer * ibo = new IndexBuffer;
	ibo->Data(sizeof(Elements), Elements);

	vao->SetIndexBuffer(ibo);
	vao->BindAttribute(0, vbo);

	//// Create VAO
	//GLuint VAO;
	//CheckedGLCall(glGenVertexArrays(1, & VAO));
	//CheckedGLCall(glBindVertexArray(VAO));

	//// Create VBO
	//GLuint VBO;
	//CheckedGLCall(glGenBuffers(1, & VBO));
	//CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	//CheckedGLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW));
	//CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	//// Bind VBO to VAO
	//CheckedGLCall(glEnableVertexAttribArray(0));
	//CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	//CheckedGLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
	//CheckedGLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

	//// Create IBO
	//GLuint EBO;
	//CheckedGLCall(glGenBuffers(1, & EBO));
	//CheckedGLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	//CheckedGLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW));

	// Compile Shader
	GLint Compiled;
	GLuint VertexShader = CheckedGLCall(glCreateShader(GL_VERTEX_SHADER));
	CheckedGLCall(glShaderSource(VertexShader, 1, & VertexShaderSource, NULL));
	CheckedGLCall(glCompileShader(VertexShader));
	CheckedGLCall(glGetShaderiv(VertexShader, GL_COMPILE_STATUS, & Compiled));
	if (! Compiled)
	{
		std::cerr << "Failed to compile vertex shader!" << std::endl;
		PrintShaderInfoLog(VertexShader);
	}

	GLuint FragmentShader = CheckedGLCall(glCreateShader(GL_FRAGMENT_SHADER));
	CheckedGLCall(glShaderSource(FragmentShader, 1, & FragmentShaderSource, NULL));
	CheckedGLCall(glCompileShader(FragmentShader));
	CheckedGLCall(glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, & Compiled));
	if (! Compiled)
	{
		std::cerr << "Failed to compile fragment shader!" << std::endl;
		PrintShaderInfoLog(FragmentShader);
	}

	GLuint ShaderProgram = CheckedGLCall(glCreateProgram());
	CheckedGLCall(glAttachShader(ShaderProgram, VertexShader));
	CheckedGLCall(glAttachShader(ShaderProgram, FragmentShader));
	CheckedGLCall(glBindFragDataLocation(ShaderProgram, 0, "outColor"));
	CheckedGLCall(glLinkProgram(ShaderProgram));
	CheckedGLCall(glUseProgram(ShaderProgram));

	CheckedGLCall(glBindAttribLocation(ShaderProgram, 0, "position"));

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		CheckedGLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		//CheckedGLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));
		vao->Draw();
		Window->SwapBuffers();
	}

	CheckedGLCall(glDeleteProgram(ShaderProgram));
	CheckedGLCall(glDeleteShader(FragmentShader));
	CheckedGLCall(glDeleteShader(VertexShader));

	delete ibo;
	delete vbo;
	delete vao;

	//CheckedGLCall(glDeleteBuffers(1, & EBO));
	//CheckedGLCall(glDeleteBuffers(1, & VBO));
	//CheckedGLCall(glDeleteVertexArrays(1, & VAO));

	return 0;
}
