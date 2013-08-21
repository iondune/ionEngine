
#pragma once

#include <SEvent.h>
#include "SKeyboardEvent.h"
#include "SMouseEvent.h"
#include "SWindowResizedEvent.h"


struct GLFWwindow;

class CWindow : public SEvent<SKeyboardEvent>::ITrigger, public SEvent<SMouseEvent>::ITrigger, public SEvent<SWindowResizedEvent>::ITrigger
{

	friend class CWindowManager;

public:

	void MakeContextCurrent();
	vec2i const & GetSize();

	bool IsKeyDown(EKey const Key);
    bool IsMouseDown(SMouseEvent::EButton const Button);
    vec2f const & GetCursorLocation();
	
	SEvent<SKeyboardEvent> KeyboardEvent;
	SEvent<SMouseEvent> MouseEvent;
	SEvent<SWindowResizedEvent> WindowResizedEvent;

protected:

	GLFWwindow * const WindowHandle;
	
	bool KeyStates[EKey::Count];
    bool MouseStates[SMouseEvent::EButton::Count];
    vec2f CursorLocation;

	vec2i Size;

private:

	CWindow(GLFWwindow * windowHandle);

};
