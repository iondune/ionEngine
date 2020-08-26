
#include "CWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace ion
{

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

	void CWindow::SetSize(vec2i const & Position)
	{
		glfwSetWindowSize(WindowHandle, Position.X, Position.Y);
	}

	vec2i const & CWindow::GetFrameBufferSize() const
	{
		return FrameBufferSize;
	}

	void CWindow::Show()
	{
		glfwShowWindow(WindowHandle);
	}

	void CWindow::SetTitle(std::string const & title)
	{
		glfwSetWindowTitle(WindowHandle, title.c_str());
	}

	float CWindow::GetAspectRatio() const
	{
		return static_cast<float>(Size.X) / static_cast<float>(Size.Y);
	}

	void CWindow::SwapBuffers()
	{
		if (GraphicsAPI->OnWindowSwap(this))
		{
			glfwSwapBuffers(WindowHandle);
		}
	}

	vec2i CWindow::GetPosition() const
	{
		vec2i Position;
		glfwGetWindowPos(WindowHandle, &Position.X, &Position.Y);
		return Position;
	}

	void CWindow::SetPosition(vec2i const & Position)
	{
		glfwSetWindowPos(WindowHandle, Position.X, Position.Y);
	}

	bool CWindow::IsKeyDown(EKey const Key)
	{
		return KeyStates[(int) Key];
	}

	bool CWindow::IsMouseDown(SMouseEvent::EButton const Button)
	{
		return MouseStates[(int) Button];
	}

	vec2f CWindow::GetCursorLocation() const
	{
		double x, y;
		glfwGetCursorPos(WindowHandle, &x, &y);
		return vec2f(vec2d(x, y));
	}

	void CWindow::SetCursorLocation(vec2f const & position)
	{
		glfwSetCursorPos(WindowHandle, position.X, position.Y);
	}

	void CWindow::SetCursorVisible(bool const Visible)
	{
		if (Visible)
		{
			glfwSetInputMode(WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	vec2f CWindow::GetRelativeCursorLocation() const
	{
		vec2f cursorLocation = GetCursorLocation();
		return cursorLocation / vec2f(Size);
	}

	void CWindow::SetRelativeCursorLocation(vec2f const & position)
	{
		glfwSetCursorPos(WindowHandle, position.X * Size.X, position.Y * Size.Y);
	}

	CWindow::CWindow(GLFWwindow * windowHandle)
		: WindowHandle(windowHandle)
	{
		for (uint i = 0; i < (uint) EKey::Count; ++ i)
			KeyStates[i] = false;

		for (uint i = 0; i < (uint) SMouseEvent::EButton::Count; ++ i)
			MouseStates[i] = false;
	}

	CWindow::~CWindow()
	{
		glfwDestroyWindow(WindowHandle);
	}

	GLFWwindow * const CWindow::GetHandle() const
	{
		return WindowHandle;
	}

	void * CWindow::GetPlatformHandle()
	{
		return glfwGetWin32Window(WindowHandle);
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

	bool CWindow::IsMinimized() const
	{
		return glfwGetWindowAttrib(WindowHandle, GLFW_ICONIFIED) != 0;
	}

	SharedPointer<Graphics::IGraphicsContext> CWindow::GetContext()
	{
		static SingletonPointer<CGraphicsAPI> GraphicsAPI;
		return GraphicsAPI->GetWindowContext(this);
	}

}
