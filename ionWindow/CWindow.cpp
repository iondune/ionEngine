
#include "CWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void CWindow::MakeContextCurrent()
{
	glfwMakeContextCurrent(WindowHandle);
}

void CWindow::Close()
{
	glfwSetWindowShouldClose(WindowHandle, true);
}

bool CWindow::ShouldClose() const
{
	return glfwWindowShouldClose(WindowHandle) != 0;
}

vec2i const & CWindow::GetSize() const
{
	return Size;
}

f32 CWindow::GetAspectRatio() const
{
	return (f32) Size.X / (f32) Size.Y;
}

void CWindow::SwapBuffers()
{
	glfwSwapBuffers(WindowHandle);
}

bool CWindow::IsKeyDown(EKey const Key)
{
	return KeyStates[(int) Key];
}

bool CWindow::IsMouseDown(SMouseEvent::EButton const Button)
{
	return MouseStates[(int) Button];
}

vec2f const & CWindow::GetCursorLocation() const
{
	return CursorLocation;
}

void CWindow::SetCursorLocation(vec2f const & position)
{
	CursorLocation = vec2f(position.X, position.Y);
	glfwSetCursorPos(WindowHandle, CursorLocation.X, CursorLocation.Y);
}

vec2f CWindow::GetRelativeCursorLocation() const
{
	return CursorLocation / vec2f(Size);
}

void CWindow::SetRelativeCursorLocation(vec2f const & position)
{
	CursorLocation = vec2f(position.X * Size.X, position.Y * Size.Y);
	glfwSetCursorPos(WindowHandle, CursorLocation.X, CursorLocation.Y);
}

CWindow::CWindow(GLFWwindow * windowHandle)
	: WindowHandle(windowHandle)
{
	for (uint i = 0; i < (uint) EKey::Count; ++ i)
        KeyStates[i] = false;

    for (uint i = 0; i < (uint) SMouseEvent::EButton::Count; ++ i)
        MouseStates[i] = false;
}

GLFWwindow * const CWindow::GetHandle() const
{
	return WindowHandle;
}

string CWindow::GetClipboardText() const
{
	return glfwGetClipboardString(WindowHandle);
}

void CWindow::SetClipboardText(string const & Text)
{
	glfwSetClipboardString(WindowHandle, Text.c_str());
}

bool CWindow::IsFocused() const
{
	return glfwGetWindowAttrib(WindowHandle, GLFW_FOCUSED) != 0;
}
