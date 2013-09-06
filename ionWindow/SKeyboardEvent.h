
#pragma once

#include <ionFramework/SEvent.h>

#include "EKey.h"


struct SKeyboardEvent : public SEventData
{
    bool Pressed;
    EKey Key;

	SKeyboardEvent()
		: Key(EKey::Unknown)
	{}
};
