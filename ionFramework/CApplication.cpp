
#include "CApplication.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


CApplication::CApplication()
	: StateManager(), SceneManager(), WindowManager()
{}

void CApplication::Init(vec2i const & WindowSize, std::string const & WindowTitle, bool const FullScreen)
{
	WindowManager = & CWindowManager::Get();
	StateManager = & CStateManager::Get();

	WindowManager->Init();
	AddWindow(WindowSize, WindowTitle, FullScreen);
	
	SceneManager = new CSceneManager(WindowSize);
}

CStateManager & CApplication::GetStateManager()
{
	return * StateManager;
}

CSceneManager & CApplication::GetSceneManager()
{
	return * SceneManager;
}

CWindowManager & CApplication::GetWindowManager()
{
	return * WindowManager;
}

CWindow & CApplication::GetWindow(uint const Index)
{
	return * Windows[Index];
}

void CApplication::AddWindow(vec2i const & WindowSize, std::string const & WindowTitle, bool const Fullscreen)
{
	Windows.push_back(WindowManager->CreateWindow(WindowSize, WindowTitle, Fullscreen));
	StateManager->Connect(Windows.back());
}

void CApplication::UpdateTime()
{
	f64 NewTime = glfwGetTime();
	ElapsedTime = NewTime - LastTime;
	RunTime += ElapsedTime;
	LastTime = NewTime;
}

void CApplication::SkipElapsedTime()
{
	LastTime = glfwGetTime();
}

f64 CApplication::GetElapsedTime() const
{
	return ElapsedTime;
}

f64 CApplication::GetRunTime() const
{
	return RunTime;
}

void CApplication::Run()
{
	Running = true;

	LastTime = glfwGetTime();
	RunTime = ElapsedTime = 0.f;

	while (Running && ! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		UpdateTime();

		StateManager->Update((f32) ElapsedTime);
		StateManager->DoStateChange();
	}

	StateManager->ShutDown();
	glfwTerminate();
}

bool CApplication::IsShuttingDown() const
{
	return ! Running;
}

void CApplication::Close()
{
	Running = false;
}
