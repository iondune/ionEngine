
#pragma once

#include <ionCore.h>


namespace ion
{

	class CWindow;

	struct SMouseEvent : public IEvent
	{
		enum class EButton
		{
			Left   = 0,
			Right  = 1,
			Middle = 2,
			Count  = 3
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
		CWindow * Window;

		SMouseEvent()
			: Window()
		{}
	};

}
