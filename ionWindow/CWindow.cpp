
#include "CWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void CWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(WindowHandle);
}

CWindow::CWindow(GLFWwindow * windowHandle)
	: WindowHandle(windowHandle)
{}
