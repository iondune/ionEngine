
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include <SEvent.h>


struct SMouseEvent : public SEventData
{
    enum class EButton
    {
        Left,
        Right,
        Middle,
        Count
    };

    enum class EType
    {
        Move,
        Click,
		Scroll
	};

    vec2f Location, Movement;
    EButton Button;
    EType Type;
    bool Pressed;
};
