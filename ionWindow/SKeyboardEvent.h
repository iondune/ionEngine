
#pragma once

#include "EKey.h"


struct SKeyboardEvent
{
    bool Pressed;
    EKey Key;

	SKeyboardEvent()
		: Key(EKey::Unknown)
	{}
};
