
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Animation
	{

		class Move
		{

		public:

			static float Linear(float From, float const To, float const Elapsed, float const Speed, float const Clamp = 0.05f);

		};

	}
}
