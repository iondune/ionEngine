
#include "CApplication.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


CApplication::CApplication()
	: StateManager(), SceneManager(), WindowManager(), Window()
{}

void CApplication::Init(vec2i const & WindowSize, std::string const & WindowTitle)
{
	WindowManager = & CWindowManager::Get();
	WindowManager->Init();

	Window = WindowManager->CreateWindow(WindowSize, WindowTitle);

	StateManager = & CStateManager::Get();
	StateManager->Connect(Window);

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

CWindow & CApplication::GetWindow()
{
	return * Window;
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

	Window->MakeContextCurrent();

	while (Running && ! Window->ShouldClose())
	{
		glfwPollEvents();

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
