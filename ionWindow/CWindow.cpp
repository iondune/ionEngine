
#include "CWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void CWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(WindowHandle);
}

CWindow::CWindow(GLFWwindow * windowHandle)
	: WindowHandle(windowHandle),
	IsKeyDown(KeyStates), MouseLocation(MousePositionState), IsMouseDown(MouseStates)
{
	for (unsigned int i = 0; i < (int) EKey::Count; ++ i)
        KeyStates[i] = false;

    for (unsigned int i = 0; i < (int) SMouseEvent::EButton::Count; ++ i)
        MouseStates[i] = false;
	
	KeyboardEvent.AddTrigger(SEvent<SKeyboardEvent>::ITrigger::shared_from_this());
	MouseEvent.AddTrigger(SEvent<SMouseEvent>::ITrigger::shared_from_this());
	WindowResizedEvent.AddTrigger(SEvent<SWindowResizedEvent>::ITrigger::shared_from_this());
}
