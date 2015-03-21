
#pragma once

#include <ionMath.h>

#include "CWindow.h"
#undef CreateWindow


enum class EWindowType
{
	Fullscreen,
	Windowed
};

class CWindowManager : public Singleton<CWindowManager>, public IEventListener
{

public:

	void Init();
	void PollEvents();
	bool ShouldClose() const;

	CWindow * CreateWindow(vec2i const & Size, std::string const & Title, EWindowType const Type);

protected:
	
	CWindow * PrimaryWindow;
	std::map<GLFWwindow *, CWindow *> Windows;

	static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
	static void MouseScrollCallback(GLFWwindow * window, double xoffset, double yoffset);
	static void MouseCursorCallback(GLFWwindow * window, double xpos, double ypos);
	static void CharCallback(GLFWwindow * window, unsigned int c);

private:
	
	friend class Singleton<CWindowManager>;
	CWindowManager();

};
