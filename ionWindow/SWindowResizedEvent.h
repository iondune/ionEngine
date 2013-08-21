
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include <SEvent.h>


struct SWindowResizedEvent : public SEventData
{
	vec2i Size;
};
