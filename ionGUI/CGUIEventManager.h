
#pragma once

#include <ionWindow.h>
#include "Gwen.h"


class CGUIEventManager : public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>
{

	Gwen::Controls::Canvas * Canvas;

public:

	CGUIEventManager(Gwen::Controls::Canvas * pCanvas, CWindow * Window);

	void OnEvent(SMouseEvent & Event);
	void OnEvent(SKeyboardEvent & Event);

};
