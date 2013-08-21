
#pragma once

#include <ionWindow.h>
#include <Gwen/Events.h>
#include <Gwen/Controls.h>


struct SUncaughtMouseEvent : public SMouseEvent
{
	SUncaughtMouseEvent(SMouseEvent const & Event)
	{
		SMouseEvent::operator =(Event);
	}
};

class CGUIEventManager : public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>, public SEvent<SUncaughtMouseEvent>::ITrigger
{

	Gwen::Controls::Canvas * Canvas;

public:

	CGUIEventManager(Gwen::Controls::Canvas * pCanvas);
	
	void OnEvent(SMouseEvent & Event);
	void OnEvent(SKeyboardEvent & Event);

	SEvent<SUncaughtMouseEvent> UncaughtMouseEvent;

};
