
#include "CWindowManager.h"

#include <ionGL.h>
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

CWindow * CWindowManager::CreateWindow(vec2i const & Size, std::string const & Title, EWindowType const Type)
{
	GLFWwindow * glfwWindow = 0;
	glfwWindowHint(GLFW_RESIZABLE, false);
	if (! (glfwWindow = glfwCreateWindow(Size.X, Size.Y, Title.c_str(), (Type == EWindowType::Fullscreen) ? glfwGetPrimaryMonitor() : 0, PrimaryWindow ? PrimaryWindow->GetHandle() : 0)))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		WaitForUser();
		exit(34);
	}

	CWindow * Window = new CWindow(glfwWindow);
	Window->Size = Size;
	Windows[glfwWindow] = Window;

	if (! PrimaryWindow)
		PrimaryWindow = Window;

	glfwSetKeyCallback(glfwWindow, CWindowManager::KeyCallback);
	glfwSetMouseButtonCallback(glfwWindow, CWindowManager::MouseButtonCallback);
	glfwSetCursorPosCallback(glfwWindow, CWindowManager::MouseCursorCallback);
	glfwSetScrollCallback(glfwWindow, CWindowManager::MouseScrollCallback);

	Window->MakeContextCurrent();
	ion::GL::Context::Init();
	glfwSwapInterval(0);

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

		int Major = 0, Minor = 0;
		char const * VersionString = (char const *) glGetString(GL_VERSION);
		if (! VersionString)
			std::cerr << "Unable to get OpenGL version number." << std::endl << std::endl;
		else if (sscanf(VersionString, "%d.%d", & Major, & Minor) != 2)
			std::cerr << "OpenGL ersion string in unknown format: " << VersionString << std::endl << std::endl;
		else if (Major < 2)
		{
			std::cerr << "Your OpenGL Version Number (" << VersionString <<
				") is not high enough for shaders. Please download and install the latest drivers"
				"for your graphics hardware." <<
				std::endl << std::endl;
		}

		std::cout << "Your OpenGL Version Number: " << VersionString << std::endl << std::endl;

		Initialized = true;
	}

	return Window;
}

CWindowManager::CWindowManager()
	: PrimaryWindow()
{}

void CWindowManager::PollEvents()
{
	glfwPollEvents();
}

bool CWindowManager::ShouldClose() const
{
	for (auto it = Windows.begin(); it != Windows.end(); ++ it)
	{
		it->second->MakeContextCurrent();
		if (it->second->ShouldClose())
		{
			return true;
		}
	}
	PrimaryWindow->MakeContextCurrent();
	return false;
}
