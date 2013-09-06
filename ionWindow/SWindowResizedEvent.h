
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include <ionFramework/SEvent.h>


struct SWindowResizedEvent : public SEventData
{
	vec2i Size;
};
