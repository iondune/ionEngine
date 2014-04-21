
#pragma once

#include <ionFramework.h>
#include "EKey.h"


class CWindow;

struct SKeyboardEvent : public IEvent
{
    bool Pressed;
    EKey Key;
	CWindow * Window;

	SKeyboardEvent()
		: Key(EKey::Unknown), Window()
	{}
};
