
#include "CWindowManager.h"
#include "ConvertGLFWKeyCode.h"

#include <GLFW/glfw3.h>


namespace ion
{

	void CWindowManager::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		CWindowManager & WindowManager = Get();
		CWindow * Window = WindowManager.Windows[window];

		SKeyboardEvent KeyEvent;
		KeyEvent.Window = Window;
		KeyEvent.Pressed = action != GLFW_RELEASE;
		KeyEvent.Key = ConvertGLFWKeyCode(key);
		KeyEvent.Modifiers = mods;

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

	void CWindowManager::CharCallback(GLFWwindow * window, unsigned int c)
	{
		CWindowManager & WindowManager = Get();
		CWindow * Window = WindowManager.Windows[window];

		SCharacterEvent Event;
		Event.C = c;
		Window->TriggerEvent(Event);
	}

	void CWindowManager::DropCallback(GLFWwindow* window, int count, const char** paths)
	{
		CWindowManager & WindowManager = Get();
		CWindow * Window = WindowManager.Windows[window];

		SFileDroppedEvent Event;
		for (int i = 0; i < count; ++ i)
		{
			Event.Paths.push_back(paths[i]);
		}
		Window->TriggerEvent(Event);
	}

}
