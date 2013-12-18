
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include <ionFramework/SEvent.h>


class CWindow;

struct SWindowResizedEvent : public SEventData
{
	vec2i Size;
	CWindow * Window;

	SWindowResizedEvent()
		: Window()
	{}
};
