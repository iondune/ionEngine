
#pragma once

#include "Gwen.h"
#include <ionWindow.h>
#include <ionFramework.h>


class CGUIEventManager : public IEventListener
{

public:

	CGUIEventManager(Gwen::Controls::Canvas * pCanvas, CWindow * Window);

	void OnEvent(IEvent & Event);

private:

	CWindow * Window;

	Gwen::Controls::Canvas * Canvas;

};
