
#pragma once

#include <ionCore.h>
#include <ionMath.h>


namespace ion
{
	namespace Animation
	{

		class Move
		{

		public:

			static float Linear(float From, float const To, float const Elapsed, float const Speed, float const Clamp = 0.05f);
			static vec3f Linear(vec3f From, vec3f const & To, float const Elapsed, float const Speed, float const Clamp = 0.05f);
			static vec3f Quadratic(vec3f From, vec3f const & To, float const Elapsed, float const Speed, float const Clamp = 0.05f);

		};

	}
}
