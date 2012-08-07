#include "CApplication.h"

#include <GL/glew.h>

#include <iostream>
#include <iomanip>

#include "CEventManager.h"
#include "CStateManager.h"

#include <SFML/Graphics.hpp>


CApplication::CApplication()
	: StateManager(0),
	SceneManager(0),
	EventManager(0)
{}

void CApplication::setupRenderContext(std::string const & WindowTitle)
{
	App = new sf::RenderWindow(sf::VideoMode(WindowSize.X, WindowSize.Y, 32), WindowTitle);

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

	//glViewport(0, 0, (GLsizei)(WindowSize.X), (GLsizei)(WindowSize.Y));
}


void CApplication::init(SPosition2 const & windowSize, std::string const & WindowTitle)
{
	WindowSize = windowSize;

	setupRenderContext(WindowTitle);

	EventManager = new CEventManager();
	StateManager = new CStateManager();
	SceneManager = new CSceneManager(windowSize);
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
	Time0 = ApplicationClock.GetElapsedTime();
}

void CApplication::updateTime()
{
	Time1 = ApplicationClock.GetElapsedTime();
	ElapsedTime = (Time1 - Time0);
	RunTime += ElapsedTime;
	Time0 = Time1;
}

EKey const ConvertSFMLKeyCode(sf::Key::Code const Code)
{
	if (Code >= sf::Key::A && Code <= sf::Key::Z)
		return EKey::a + (Code - sf::Key::A);

	if (Code >= sf::Key::Num0 && Code <= sf::Key::Num9)
		return EKey::NUM_0 + (Code - sf::Key::Num0);

	return EKey::Unknown;
}

void CApplication::run()
{
	Running = true;

	Time0 = ApplicationClock.GetElapsedTime();

	RunTime = ElapsedTime = 0.f;

	while (Running && App->IsOpened())
	{
		sf::Event Event;
		while (App->GetEvent(Event))
		{
			switch (Event.Type)
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
					MouseEvent.Pressed = Event.Type == sf::Event::MouseButtonPressed;

					switch (Event.MouseButton.Button)
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
					MouseEvent.Location = EventManager->MousePositionState = SPosition2(Event.MouseMove.X, Event.MouseMove.Y);
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
					KeyEvent.Pressed = Event.Type == sf::Event::KeyPressed;
					KeyEvent.Key = ConvertSFMLKeyCode(Event.Key.Code);
					EventManager->OnKeyboardEvent(KeyEvent);
					EventManager->KeyStates[KeyEvent.Key] = KeyEvent.Pressed;

					break;

				}
			} // switch (Event.type)
		} // while (SDL_PollEvent(& Event))*/

		updateTime();

		EventManager->OnGameTickStart(ElapsedTime);
		EventManager->OnGameTickEnd(ElapsedTime);

		EventManager->OnRenderStart(ElapsedTime);
		EventManager->OnRenderEnd(ElapsedTime);

		StateManager->doStateChange();

	} // while (Running)

	StateManager->shutDown();
}

float const CApplication::getElapsedTime() const
{
	return ElapsedTime;
}

float const CApplication::getRunTime() const
{
	return RunTime;
}

float const CApplication::getAspectRatio()
{
	return (float)get().WindowSize.X/(float)get().WindowSize.Y;
}

SPosition2 const & CApplication::getWindowSize() const
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
