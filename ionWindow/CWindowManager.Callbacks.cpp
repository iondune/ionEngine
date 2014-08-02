
#include "CWindowManager.h"
#include "ConvertGLFWKeyCode.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void CWindowManager::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SKeyboardEvent KeyEvent;
	KeyEvent.Window = Window;
	KeyEvent.Pressed = action != GLFW_RELEASE;
	KeyEvent.Key = ConvertGLFWKeyCode(key);

	Window->KeyStates[(int) KeyEvent.Key] = KeyEvent.Pressed;
	Window->TriggerEvent(KeyEvent);
}

void CWindowManager::MouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SMouseEvent MouseEvent;
	MouseEvent.Window = Window;
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
	Window->TriggerEvent(MouseEvent);
}

void CWindowManager::MouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SMouseEvent MouseEvent;
	MouseEvent.Window = Window;
	MouseEvent.Type = SMouseEvent::EType::Scroll;
	MouseEvent.Movement = vec2d(xoffset, yoffset);

	Window->TriggerEvent(MouseEvent);
}

void CWindowManager::MouseCursorCallback(GLFWwindow * window, double xpos, double ypos)
{
	CWindowManager & WindowManager = Get();
	CWindow * Window = WindowManager.Windows[window];

	SMouseEvent MouseEvent;
	MouseEvent.Window = Window;
	MouseEvent.Type = SMouseEvent::EType::Move;
	MouseEvent.Location = vec2d(xpos, ypos);

	MouseEvent.Movement = MouseEvent.Location - Window->CursorLocation;
	Window->CursorLocation = MouseEvent.Location;

	Window->TriggerEvent(MouseEvent);
}
