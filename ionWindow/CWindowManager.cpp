
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

CWindow * CWindowManager::CreateWindow(vec2i const & Size, std::string const & Title, bool const FullScreen)
{
	GLFWwindow * glfwWindow = 0;
	glfwWindowHint(GLFW_RESIZABLE, false);
	if (! (glfwWindow = glfwCreateWindow(Size.X, Size.Y, Title.c_str(), FullScreen ? glfwGetPrimaryMonitor() : 0, 0)))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		WaitForUser();
		exit(34);
	}
	
	CWindow * Window = new CWindow(glfwWindow);
	Window->Size = Size;
	Windows[glfwWindow] = Window;
	
	glfwSetKeyCallback(glfwWindow, CWindowManager::KeyCallback);
	glfwSetMouseButtonCallback(glfwWindow, CWindowManager::MouseButtonCallback);
	glfwSetCursorPosCallback(glfwWindow, CWindowManager::MouseCursorCallback);
	glfwSetScrollCallback(glfwWindow, CWindowManager::MouseScrollCallback);

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

	return Window;
}

EKey const ConvertGLFWKeyCode(int const Code)
{
	if (Code >= 'A' && Code <= 'Z')
		return (EKey) ((int) EKey::A + (Code - 'A'));
	
	if (Code >= GLFW_KEY_KP_0 && Code <= GLFW_KEY_KP_9)
		return (EKey) ((int) EKey::KeyPad0 + (Code - GLFW_KEY_KP_0));
	if (Code >= '0' && Code <= '9')
		return (EKey) ((int) EKey::Num0 + (Code - '0'));
	
	switch (Code)
	{

	case '[':
		return EKey::LeftBracket;
	case ']':
		return EKey::RightBracket;
	case ',':
		return EKey::Comma;
	case '.':
		return EKey::Period;
	case ';':
		return EKey::Semicolon;
	case '\'':
		return EKey::Quote;
	case '/':
		return EKey::Slash;
	case '\\':
		return EKey::BackSlash;
	case '`':
		return EKey::Grave;

	case GLFW_KEY_ESCAPE:
		return EKey::Escape;
		
	case GLFW_KEY_UP:
		return EKey::Up;
	case GLFW_KEY_LEFT:
		return EKey::Left;
	case GLFW_KEY_DOWN:
		return EKey::Down;
	case GLFW_KEY_RIGHT:
		return EKey::Right;
		
	case GLFW_KEY_SPACE:
		return EKey::Space;
		
	case GLFW_KEY_LEFT_SHIFT:
		return EKey::LeftShift;
	case GLFW_KEY_RIGHT_SHIFT:
		return EKey::RightShift;
	case GLFW_KEY_LEFT_CONTROL:
		return EKey::LeftControl;
	case GLFW_KEY_RIGHT_CONTROL:
		return EKey::RightControl;
	case GLFW_KEY_LEFT_ALT:
		return EKey::LeftAlt;
	case GLFW_KEY_RIGHT_ALT:
		return EKey::RightAlt;
		
	case GLFW_KEY_F1:
		return EKey::F1;
	case GLFW_KEY_F2:
		return EKey::F2;
	case GLFW_KEY_F3:
		return EKey::F3;
	case GLFW_KEY_F4:
		return EKey::F4;
	case GLFW_KEY_F5:
		return EKey::F5;
	case GLFW_KEY_F6:
		return EKey::F6;
	case GLFW_KEY_F7:
		return EKey::F7;
	case GLFW_KEY_F8:
		return EKey::F8;
	case GLFW_KEY_F9:
		return EKey::F9;
	case GLFW_KEY_F10:
		return EKey::F10;
	case GLFW_KEY_F11:
		return EKey::F11;
	case GLFW_KEY_F12:
		return EKey::F12;

	default:
		return EKey::Unknown;

	};
}

void CWindowManager::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SKeyboardEvent KeyEvent;
	KeyEvent.Pressed = action != GLFW_RELEASE;
	KeyEvent.Key = ConvertGLFWKeyCode(key);
	
	Window->KeyStates[(int) KeyEvent.Key] = KeyEvent.Pressed;
	Window->SEvent<SKeyboardEvent>::ITrigger::Trigger(KeyEvent);
}

void CWindowManager::MouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SMouseEvent MouseEvent;
	MouseEvent.Type = SMouseEvent::EType::Click;
	MouseEvent.Location = Window->CursorLocation;
	MouseEvent.Pressed = action == GLFW_PRESS;

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		MouseEvent.Button = SMouseEvent::EButton::Left;
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		MouseEvent.Button = SMouseEvent::EButton::Right;
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		MouseEvent.Button = SMouseEvent::EButton::Middle;
		break;

	default:
		break;
	}

	Window->MouseStates[(int) MouseEvent.Button] = MouseEvent.Pressed;
	Window->SEvent<SMouseEvent>::ITrigger::Trigger(MouseEvent);
}

void CWindowManager::MouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SMouseEvent MouseEvent;
	MouseEvent.Type = SMouseEvent::EType::Scroll;
	MouseEvent.Movement = vec2d(xoffset, yoffset);

	Window->SEvent<SMouseEvent>::ITrigger::Trigger(MouseEvent);
}

void CWindowManager::MouseCursorCallback(GLFWwindow * window, double xpos, double ypos)
{	
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SMouseEvent MouseEvent;
	MouseEvent.Type = SMouseEvent::EType::Move;
	MouseEvent.Location = vec2d(xpos, ypos);

	MouseEvent.Movement = MouseEvent.Location - Window->CursorLocation;
	Window->CursorLocation = MouseEvent.Location;
	
	Window->SEvent<SMouseEvent>::ITrigger::Trigger(MouseEvent);
}

CWindowManager::CWindowManager()
{}

void CWindowManager::PollEvents()
{
	glfwPollEvents();

	GamePad.UpdateState();
}