
#include "ConvertGLFWKeyCode.h"

#include <GLFW/glfw3.h>


namespace ion
{

	EKey const ConvertGLFWKeyCode(int const Code)
	{
		if (Code >= GLFW_KEY_A && Code <= GLFW_KEY_Z)
		{
			return (EKey) ((int) EKey::A + (Code - GLFW_KEY_A));
		}
		if (Code >= GLFW_KEY_KP_0 && Code <= GLFW_KEY_KP_9)
		{
			return (EKey) ((int) EKey::KeyPad0 + (Code - GLFW_KEY_KP_0));
		}
		if (Code >= GLFW_KEY_0 && Code <= GLFW_KEY_9)
		{
			return (EKey) ((int) EKey::Num0 + (Code - GLFW_KEY_0));
		}
		if (Code >= GLFW_KEY_F1 && Code <= GLFW_KEY_F15)
		{
			return (EKey) ((int) EKey::F1 + (Code - GLFW_KEY_F1));
		}

		switch (Code)
		{
		case GLFW_KEY_SPACE:
			return EKey::Space;
		case GLFW_KEY_APOSTROPHE:
			return EKey::Quote;
		case GLFW_KEY_COMMA:
			return EKey::Comma;
		case GLFW_KEY_MINUS:
			return EKey::Minus;
		case GLFW_KEY_PERIOD:
			return EKey::Period;
		case GLFW_KEY_SLASH:
			return EKey::Slash;

		case GLFW_KEY_SEMICOLON:
			return EKey::Semicolon;
		case GLFW_KEY_EQUAL:
			return EKey::Equals;

		case GLFW_KEY_LEFT_BRACKET:
			return EKey::LeftBracket;
		case GLFW_KEY_BACKSLASH:
			return EKey::BackSlash;
		case GLFW_KEY_RIGHT_BRACKET:
			return EKey::RightBracket;
		case GLFW_KEY_GRAVE_ACCENT:
			return EKey::Grave;

		case GLFW_KEY_ESCAPE:
			return EKey::Escape;
		case GLFW_KEY_ENTER:
			return EKey::Enter;
		case GLFW_KEY_TAB:
			return EKey::Tab;
		case GLFW_KEY_BACKSPACE:
			return EKey::Backspace;
		case GLFW_KEY_INSERT:
			return EKey::Insert;
		case GLFW_KEY_DELETE:
			return EKey::Delete;

		case GLFW_KEY_RIGHT:
			return EKey::Right;
		case GLFW_KEY_LEFT:
			return EKey::Left;
		case GLFW_KEY_DOWN:
			return EKey::Down;
		case GLFW_KEY_UP:
			return EKey::Up;

		case GLFW_KEY_PAGE_UP:
			return EKey::PageUp;
		case GLFW_KEY_PAGE_DOWN:
			return EKey::PageDown;
		case GLFW_KEY_HOME:
			return EKey::Home;
		case GLFW_KEY_END:
			return EKey::End;

		case GLFW_KEY_CAPS_LOCK:
			return EKey::CapsLock;
		case GLFW_KEY_SCROLL_LOCK:
			return EKey::ScrollLock;
		case GLFW_KEY_NUM_LOCK:
			return EKey::NumLock;
		case GLFW_KEY_PRINT_SCREEN:
			return EKey::PrintScreen;
		case GLFW_KEY_PAUSE:
			return EKey::Pause;

		case GLFW_KEY_KP_DECIMAL:
			return EKey::KeyPadDecimal;
		case GLFW_KEY_KP_DIVIDE:
			return EKey::KeyPadDivide;
		case GLFW_KEY_KP_MULTIPLY:
			return EKey::KeyPadMultiply;
		case GLFW_KEY_KP_SUBTRACT:
			return EKey::KeyPadSubtract;
		case GLFW_KEY_KP_ADD:
			return EKey::KeyPadAdd;
		case GLFW_KEY_KP_ENTER:
			return EKey::KeyPadEnter;
		case GLFW_KEY_KP_EQUAL:
			return EKey::KeyPadEquals;

		case GLFW_KEY_LEFT_SHIFT:
			return EKey::LeftShift;
		case GLFW_KEY_LEFT_CONTROL:
			return EKey::LeftControl;
		case GLFW_KEY_LEFT_ALT:
			return EKey::LeftAlt;
		case GLFW_KEY_LEFT_SUPER:
			return EKey::LeftSuper;

		case GLFW_KEY_RIGHT_SHIFT:
			return EKey::RightShift;
		case GLFW_KEY_RIGHT_CONTROL:
			return EKey::RightControl;
		case GLFW_KEY_RIGHT_ALT:
			return EKey::RightAlt;
		case GLFW_KEY_RIGHT_SUPER:
			return EKey::RightSuper;

		case GLFW_KEY_MENU:
			return EKey::Menu;

		default:
			return EKey::Unknown;

		};
	}

}
