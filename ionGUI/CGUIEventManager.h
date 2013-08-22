
#pragma once

#include <ionWindow.h>
#include <Gwen/Events.h>
#include <Gwen/Controls.h>


class CGUIEventManager : public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>
{

	Gwen::Controls::Canvas * Canvas;

public:

	CGUIEventManager(Gwen::Controls::Canvas * pCanvas);
	
	void OnEvent(SMouseEvent & Event);
	void OnEvent(SKeyboardEvent & Event);

};
