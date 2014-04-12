
#pragma once

#include "Gwen.h"
#include <ionFramework/CWindow.h>
#include <ionFramework/IEventListener.h>


class CGUIEventManager : public IEventListener
{

	Gwen::Controls::Canvas * Canvas;

public:

	CGUIEventManager(Gwen::Controls::Canvas * pCanvas, CWindow * Window);

	void OnEvent(IEvent & Event);

};
