
#include "CWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace ion
{

	CWindow * CWindow::CurrentContext = nullptr;

	void CWindow::MakeContextCurrent()
	{
		if (this != CurrentContext)
		{
			glfwMakeContextCurrent(WindowHandle);
			CurrentContext = this;
		}
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

	vec2i const & CWindow::GetFrameBufferSize() const
	{
		return FrameBufferSize;
	}

	f32 CWindow::GetAspectRatio() const
	{
		return (f32) Size.X / (f32) Size.Y;
	}

	void CWindow::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle);
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

	SharedPointer<Graphics::IGraphicsContext> CWindow::GetContext()
	{
		static SingletonPointer<CGraphicsAPI> GraphicsAPI;
		return GraphicsAPI->GetWindowContext(this);
	}

}
