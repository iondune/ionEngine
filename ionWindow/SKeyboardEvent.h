
#pragma once

#include <ionCore.h>
#include "EKey.h"


namespace ion
{

	class CWindow;

	struct SKeyboardEvent : public IEvent
	{
		bool Pressed = false;
		EKey Key = EKey::Unknown;
		CWindow * Window = nullptr;
	};

	struct SCharacterEvent : public IEvent
	{
		char C = 0;
	};

}
