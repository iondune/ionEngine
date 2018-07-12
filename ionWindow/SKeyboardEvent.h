
#pragma once

#include <ionCore.h>
#include "EKey.h"


namespace ion
{

	class CWindow;

	enum class EKeyboardEventType
	{
		Press,
		Repeat,
		Release
	};

	struct SKeyboardEvent : public IEvent
	{
		bool Pressed = false;
		EKeyboardEventType Type = EKeyboardEventType::Press;
		EKey Key = EKey::Unknown;
		int Modifiers = 0x0;
		CWindow * Window = nullptr;
	};

	struct SCharacterEvent : public IEvent
	{
		char C = 0;
	};

}
