
#pragma once

#include <ionCore.h>


namespace ion
{

	class CWindow;

	struct SFileDroppedEvent : public IEvent
	{
		vector<string> Paths;
		CWindow * Window = nullptr;
	};

}
