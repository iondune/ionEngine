#include "CApplication.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <iomanip>

#include "CEventManager.h"
#include "CStateManager.h"


static GLFWwindow * window;

CApplication::CApplication()
	: StateManager(0),
	SceneManager(0),
	EventManager(0)
{}

void CApplication::setupRenderContext(std::string const & WindowTitle)
{

}


void CApplication::init(vec2i const & windowSize, std::string const & WindowTitle)
{
	WindowSize = windowSize;

	setupRenderContext(WindowTitle);

	// TO DO : Engines need to be initialized at this point so that callbacks that access the eventmananger don't fail.

	glfwSetKeyCallback(window, CApplication::KeyCallback);
	glfwSetMouseButtonCallback(window, CApplication::MouseButtonCallback);
	glfwSetCursorPosCallback(window, CApplication::MouseCursorCallback);
	glfwSetScrollCallback(window, CApplication::MouseScrollCallback);
}

void CApplication::loadEngines()
{
	EventManager = new CEventManager();
	StateManager = new CStateManager();
	SceneManager = new CSceneManager(WindowSize);
}

CApplication & CApplication::get()
{
	static CApplication SingletonInstance;

	return SingletonInstance;
}

CEventManager & CApplication::getEventManager()
{
	return * EventManager;
}

CStateManager & CApplication::getStateManager()
{
	return * StateManager;
}

CSceneManager & CApplication::getSceneManager()
{
	return * SceneManager;
}

void CApplication::skipElapsedTime()
{
	Time0 = glfwGetTime();
}

void CApplication::updateTime()
{
	Time1 = glfwGetTime();
	ElapsedTime = /*min(0.1, */(Time1 - Time0);//);
	RunTime += ElapsedTime;
	Time0 = Time1;
}

void CApplication::run()
{
	Running = true;

	Time0 = glfwGetTime();

	RunTime = ElapsedTime = 0.f;

	glfwMakeContextCurrent(window);

	while (Running && ! glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		/*sf::Event Event;
		while (App->pollEvent(Event))
		{
			EventManager->OnSFMLEvent(Event);
			switch (Event.type)
			{

			case sf::Event::Closed:
				Running = false;
				break;

			case sf::Event::Resized:
				{

					SWindowResizedEvent WindowEvent;
					WindowEvent.Size.X = Event.size.width;
					WindowEvent.Size.Y = Event.size.height;
					WindowSize = WindowEvent.Size;
					EventManager->OnWindowResized(WindowEvent);
					SceneManager->OnWindowResized(WindowSize);
					

					App->setView(sf::View(sf::FloatRect(0, 0, (float) Event.size.width, (float) Event.size.height)));

					break;

				}
			} // switch (Event.type)
		} // while (SDL_PollEvent(& Event))*/

		updateTime();

		EventManager->OnGameTickStart((f32) ElapsedTime);
		EventManager->OnGameTickEnd((f32) ElapsedTime);

		EventManager->OnRenderStart((f32) ElapsedTime);
		EventManager->OnRenderEnd((f32) ElapsedTime);

		StateManager->doStateChange();

	} // while (Running)

	StateManager->shutDown();
	glfwTerminate();
}

f64 CApplication::getElapsedTime() const
{
	return ElapsedTime;
}

f64 CApplication::getRunTime() const
{
	return RunTime;
}

float const CApplication::getAspectRatio()
{
	return (float) WindowSize.X / (float) WindowSize.Y;
}

vec2i const & CApplication::getWindowSize() const
{
	return WindowSize;
}

bool CApplication::isShuttingDown() const
{
	return ! Running;
}

void CApplication::close()
{
	Running = false;
}

void CApplication::swapBuffers()
{
	glfwSwapBuffers(window);
}
