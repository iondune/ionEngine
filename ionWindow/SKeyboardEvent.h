
#pragma once

#include <ionFramework.h>
#include "EKey.h"


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
