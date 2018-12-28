
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

}
