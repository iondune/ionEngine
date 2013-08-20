
#include "CWindowManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void CWindowManager::Init()
{
	static bool Initialized = false;

	if (Initialized)
		return;

	if (! glfwInit())
	{
		std::cerr << "Error initializing glfw! " << std::endl;
		WaitForUser();
		exit(33);
	}

	Initialized = true;
}

CWindow * CWindowManager::CreateWindow(vec2i const & Size, std::string const & Title)
{
	GLFWwindow * glfwWindow = 0;
	glfwWindowHint(GLFW_RESIZABLE, false);
	if (! (glfwWindow = glfwCreateWindow(Size.X, Size.Y, Title.c_str(), 0, 0)))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		WaitForUser();
		exit(34);
	}
	
	CWindow * Window = new CWindow(glfwWindow);
	Window->MakeContextCurrent();

	static bool Initialized = false;

	if (! Initialized)
	{
		u32 Error = glewInit();
		if (Error != GLEW_OK)
		{
			std::cerr << "Error initializing glew! " << glewGetErrorString(Error) << std::endl;
			WaitForUser();
			exit(33);
		}
		double const VersionNumber = std::atof((char const *) glGetString(GL_VERSION));
		if (VersionNumber < 2.0)
		{
			std::cerr << "Your OpenGL Version Number (" << std::setprecision(2) << VersionNumber << 
				") is not high enough for shaders. Please download and install the latest drivers"
				"for your graphics hardware." << 
				std::endl << std::endl;
		}

		std::cout << "Your OpenGL Version Number: " << std::setprecision(2) << VersionNumber << std::endl << std::endl;

		Initialized = true;
	}
}
