
#pragma once

#include <ionCore.h>


namespace ion
{

	class CWindow;

	struct SWindowResizedEvent : public IEvent
	{
		vec2i Size;
		CWindow * Window;

		SWindowResizedEvent()
			: Window()
		{}
	};

	struct SWindowMovedEvent : public IEvent
	{
		vec2i Pos;
		CWindow * Window;

		SWindowMovedEvent()
			: Window()
		{}
	};

	struct SWindowClosedEvent : public IEvent
	{
		CWindow * Window;

		SWindowClosedEvent()
			: Window()
		{}
	};

}
