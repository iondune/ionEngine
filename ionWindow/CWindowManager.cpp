
#include "CWindowManager.h"

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

	SingletonPointer<CStateManager> StateManager;
	AddListener(StateManager.Get());

	Initialized = true;
}

CWindow * CWindowManager::CreateWindow(vec2i const & Size, std::string const & Title, EWindowType const Type)
{
	GLFWwindow * glfwWindow = 0;
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (! (glfwWindow = glfwCreateWindow(Size.X, Size.Y, Title.c_str(), (Type == EWindowType::Fullscreen) ? glfwGetPrimaryMonitor() : nullptr, PrimaryWindow ? PrimaryWindow->GetHandle() : nullptr)))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		WaitForUser();
		exit(34);
	}

	CWindow * Window = new CWindow(glfwWindow);
	Window->Size = Size;
	Windows[glfwWindow] = Window;

	if (! PrimaryWindow)
	{
		PrimaryWindow = Window;
	}

	glfwSetKeyCallback(glfwWindow, CWindowManager::KeyCallback);
	glfwSetMouseButtonCallback(glfwWindow, CWindowManager::MouseButtonCallback);
	glfwSetCursorPosCallback(glfwWindow, CWindowManager::MouseCursorCallback);
	glfwSetScrollCallback(glfwWindow, CWindowManager::MouseScrollCallback);
	glfwSetCharCallback(glfwWindow, CWindowManager::CharCallback);

	Window->AddListener(this);

	Window->MakeContextCurrent();
	glfwSwapInterval(0);

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
		if (Windows.size() > 1)
		{
			it->second->MakeContextCurrent();
		}

		if (it->second->ShouldClose())
		{
			return true;
		}
	}
	if (Windows.size() > 1)
	{
		PrimaryWindow->MakeContextCurrent();
	}
	return false;
}

bool CWindowManager::Run()
{
	bool Done = ShouldClose();
	PollEvents();
	return ! Done;
}
