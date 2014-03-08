
#include "ConvertGLFWKeyCode.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


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
