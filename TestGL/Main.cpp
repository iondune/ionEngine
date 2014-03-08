
#include <ionEngine.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", false);

	char const * VertexShaderSource =
		"	#version 150		\n"
		"	in vec2 position;	\n"
		"	void main()			\n"
		"	{					\n"
		"		gl_Position = vec4(position, 0.0, 1.0);	\n"
		"	}					\n";

	char const * FragmentShaderSource =
		"	#version 150			\n"
		"	out vec4 outColor;		\n"
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
		0, 1, 2,
		2, 3, 0
	};

	GLuint VAO;
	glGenVertexArrays(1, & VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, & VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	GLuint EBO;
	glGenBuffers(1, & EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW);

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, & VertexShaderSource, NULL);
	glCompileShader(VertexShader);

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, & FragmentShaderSource, NULL);
	glCompileShader(FragmentShader);

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glBindFragDataLocation(ShaderProgram, 0, "outColor");
	glLinkProgram(ShaderProgram);
	glUseProgram(ShaderProgram);

	GLint PositionAttribute = glGetAttribLocation(ShaderProgram, "position");
	glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(PositionAttribute);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Window->SwapBuffers();
	}

	glDeleteProgram(ShaderProgram);
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);

	glDeleteBuffers(1, & EBO);
	glDeleteBuffers(1, & VBO);
	glDeleteVertexArrays(1, & VAO);

	return 0;
}
