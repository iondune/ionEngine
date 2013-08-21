
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
	
	SEvent<SKeyboardEvent> KeyboardEvent;
	SEvent<SMouseEvent> MouseEvent;
	SEvent<SWindowResizedEvent> WindowResizedEvent;

	bool const (& IsKeyDown)[EKey::Count];
    bool const (& IsMouseDown)[SMouseEvent::EButton::Count];

    vec2f const & MouseLocation;

protected:

	GLFWwindow * const WindowHandle;
	
	bool KeyStates[EKey::Count];
    bool MouseStates[SMouseEvent::EButton::Count];
    vec2f MousePositionState;
	vec2f LastMousePosition;

private:

	CWindow(GLFWwindow * windowHandle);

};
