#include "CApplication.h"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>
#include <iomanip>

#include "CEventManager.h"
#include "CStateManager.h"


CApplication::CApplication()
	: StateManager(0),
	SceneManager(0),
	EventManager(0)
{}

void CApplication::setupRenderContext(std::string const & WindowTitle)
{
	if (!glfwInit())
	{
		std::cerr << "Error initializing glfw! " << std::endl;
		waitForUser();
		exit(3);
	}

	if (!glfwOpenWindow(WindowSize.X, WindowSize.Y, 8, 8, 8, 0, 24, 0, GLFW_WINDOW))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		waitForUser();
		exit(3);
	}

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error initializing glew! " << glewGetErrorString(err) << std::endl;
		waitForUser();
		exit(3);
	}

	double const VersionNumber = std::atof((char const *)glGetString(GL_VERSION));
	if (VersionNumber < 2.0)
	{
		std::cerr << "Your OpenGL Version Number (" << std::setprecision(2) << VersionNumber << 
			") is not high enough for shaders. Please download and install the latest drivers"
			"for your graphics hardware." << 
			std::endl << std::endl;
	}

	std::cerr << "Your OpenGL Version Number: " << std::setprecision(2) << VersionNumber << std::endl << std::endl;
}



EKey const ConvertGLFWKeyCode(int const Code)
{
	if (Code >= 'a' && Code <= 'z')
		return EKey::A + (Code - 'a');

	if (Code >= GLFW_KEY_KP_0 && Code <= GLFW_KEY_KP_9)
		return EKey::Num0 + (Code - GLFW_KEY_KP_0);

	switch (Code)
	{

	case GLFW_KEY_ESC:
		return EKey::Escape;
		
	case GLFW_KEY_UP:
		return EKey::Up;
	case GLFW_KEY_LEFT:
		return EKey::Left;
	case GLFW_KEY_DOWN:
		return EKey::Down;
	case GLFW_KEY_RIGHT:
		return EKey::Right;

	default:
		return EKey::Unknown;

	};
}

void CApplication::KeyCallback(int key, int action)
{
	CApplication & Application = CApplication::get();

	SKeyboardEvent KeyEvent;
	KeyEvent.Pressed = action == GLFW_PRESS;
	KeyEvent.Key = ConvertGLFWKeyCode(key);
	Application.EventManager->OnKeyboardEvent(KeyEvent);
	Application.EventManager->KeyStates[KeyEvent.Key] = KeyEvent.Pressed;
}

void CApplication::init(vec2i const & windowSize, std::string const & WindowTitle)
{
	WindowSize = windowSize;

	setupRenderContext(WindowTitle);

	glfwSetKeyCallback(CApplication::KeyCallback);
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
	ElapsedTime = min(0.1, (Time1 - Time0));
	RunTime += ElapsedTime;
	Time0 = Time1;
}

void CApplication::run()
{
	Running = true;

	Time0 = glfwGetTime();

	RunTime = ElapsedTime = 0.f;

	while (Running && glfwGetWindowParam(GLFW_OPENED))
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

			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
				{

					SMouseEvent MouseEvent;
					MouseEvent.Type = SMouseEvent::EType::Click;
					MouseEvent.Location = EventManager->MouseLocation;
					MouseEvent.RelativeLocation = SVector2f(MouseEvent.Location.X / (float) WindowSize.X,
						MouseEvent.Location.Y / (float) WindowSize.Y);
					MouseEvent.Pressed = Event.type == sf::Event::MouseButtonPressed;

					switch (Event.mouseButton.button)
					{

					case sf::Mouse::Left:
						MouseEvent.Button = SMouseEvent::EButton::Left;
						EventManager->MouseStates[SMouseEvent::EButton::Left] = MouseEvent.Pressed;
						EventManager->OnMouseEvent(MouseEvent);
						break;

					case sf::Mouse::Right:
						MouseEvent.Button = SMouseEvent::EButton::Right;
						EventManager->MouseStates[SMouseEvent::EButton::Right] = MouseEvent.Pressed;
						EventManager->OnMouseEvent(MouseEvent);
						break;

					case sf::Mouse::Middle:
						MouseEvent.Button = SMouseEvent::EButton::Middle;
						EventManager->MouseStates[SMouseEvent::EButton::Middle] = MouseEvent.Pressed;
						EventManager->OnMouseEvent(MouseEvent);
						break;

					default:
						break;

					}

					break;

				}

			case sf::Event::MouseMoved:
				{

					SMouseEvent MouseEvent;
					MouseEvent.Type = SMouseEvent::EType::Move;
					MouseEvent.Location = EventManager->MousePositionState = SPosition2(Event.mouseMove.x, Event.mouseMove.y);
					MouseEvent.RelativeLocation = SVector2f(MouseEvent.Location.X / (float) WindowSize.X,
						MouseEvent.Location.Y / (float) WindowSize.Y);
					MouseEvent.Movement = MouseEvent.Location - LastMouse;
					EventManager->OnMouseEvent(MouseEvent);

					LastMouse = MouseEvent.Location;

					break;

				}

			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
				{

					SKeyboardEvent KeyEvent;
					KeyEvent.Pressed = Event.type == sf::Event::KeyPressed;
					KeyEvent.Key = ConvertSFMLKeyCode(Event.key.code);
					EventManager->OnKeyboardEvent(KeyEvent);
					EventManager->KeyStates[KeyEvent.Key] = KeyEvent.Pressed;

					break;

				}

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
	glfwSwapBuffers();
}
