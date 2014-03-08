
#pragma once

#include "IEventListener.h"
#include "SKeyboardEvent.h"
#include "SMouseEvent.h"
#include "SWindowResizedEvent.h"


struct GLFWwindow;

class CWindow : public IEventListener
{

	friend class CWindowManager;

public:

	void MakeContextCurrent();
	bool ShouldClose() const;
	vec2i const & GetSize() const;
	f32 GetAspectRatio() const;
	void SwapBuffers();

	bool IsKeyDown(EKey const Key);
    bool IsMouseDown(SMouseEvent::EButton const Button);

    vec2f const & GetCursorLocation() const;
	void SetCursorLocation(vec2f const & position);

    vec2f GetRelativeCursorLocation() const;
	void SetRelativeCursorLocation(vec2f const & position);
	
	GLFWwindow * const GetHandle() const;

protected:

	GLFWwindow * const WindowHandle;
	
	bool KeyStates[EKey::Count];
    bool MouseStates[SMouseEvent::EButton::Count];
    vec2f CursorLocation;

	vec2i Size;

private:

	CWindow(GLFWwindow * windowHandle);

};
