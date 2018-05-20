
#pragma once

#include <ionCore.h>
#include <ionGraphics.h>

#include "SKeyboardEvent.h"
#include "SMouseEvent.h"


struct GLFWwindow;

namespace ion
{

	class CWindow : public IEventListener
	{

		friend class CWindowManager;

	public:

		void MakeContextCurrent();
		bool ShouldClose() const;
		void Close();

		vec2i const & GetSize() const;
		vec2i const & GetFrameBufferSize() const;

		float GetAspectRatio() const;
		void SwapBuffers();

		vec2i GetPosition() const;
		void SetPosition(vec2i const & Position);

		bool IsKeyDown(EKey const Key);
		bool IsMouseDown(SMouseEvent::EButton const Button);

		vec2f const & GetCursorLocation() const;
		void SetCursorLocation(vec2f const & position);
		void SetCursorVisible(bool const Visible);

		vec2f GetRelativeCursorLocation() const;
		void SetRelativeCursorLocation(vec2f const & position);

		GLFWwindow * const GetHandle() const;

		string GetClipboardText() const;
		void SetClipboardText(string const & Text);

		bool IsFocused() const;

		SharedPointer<Graphics::IGraphicsContext> GetContext();

	protected:

		CGraphicsAPI * GraphicsAPI = nullptr;
		GLFWwindow * const WindowHandle;

		bool KeyStates[(int) EKey::Count];
		bool MouseStates[(int) SMouseEvent::EButton::Count];
		vec2f CursorLocation;

		vec2i Size;
		vec2i FrameBufferSize;

	private:

		CWindow(GLFWwindow * windowHandle);

		static CWindow * CurrentContext;

	};

}
