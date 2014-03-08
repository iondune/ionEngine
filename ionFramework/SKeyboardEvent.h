
#pragma once

#include <ionFramework/SEvent.h>

#include "EKey.h"


class CWindow;

struct SKeyboardEvent : public SEventData
{
    bool Pressed;
    EKey Key;
	CWindow * Window;

	SKeyboardEvent()
		: Key(EKey::Unknown), Window()
	{}
};
