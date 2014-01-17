
#pragma once

#include <ionFramework/SEvent.h>
#include "SKeyboardEvent.h"
#include "SMouseEvent.h"
#include "SWindowResizedEvent.h"


struct GLFWwindow;

class CWindow : public SEvent<SKeyboardEvent>::ITrigger, public SEvent<SMouseEvent>::ITrigger, public SEvent<SWindowResizedEvent>::ITrigger
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
	
	SEvent<SKeyboardEvent> KeyboardEvent;
	SEvent<SMouseEvent> MouseEvent;
	SEvent<SWindowResizedEvent> WindowResizedEvent;
	
	GLFWwindow * const GetHandle();

protected:

	GLFWwindow * const WindowHandle;
	
	bool KeyStates[EKey::Count];
    bool MouseStates[SMouseEvent::EButton::Count];
    vec2f CursorLocation;

	vec2i Size;

private:

	CWindow(GLFWwindow * windowHandle);

};
