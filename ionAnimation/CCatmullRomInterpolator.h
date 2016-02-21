
#pragma once

#include "IInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CCatmullRomInterpolator : public IInterpolator<T>
		{

		public:

			virtual T const Interpolate(IPath<T> const & Path, s32 const Index, float const Mu);

		};

		template <typename T>
		T const CCatmullRomInterpolator<T>::Interpolate(IPath<T> const & Path, s32 const Index, float const Mu)
		{
			T const P0 = Path.GetNode(Index - 1);
			T const P1 = Path.GetNode(Index + 0);
			T const P2 = Path.GetNode(Index + 1);
			T const P3 = Path.GetNode(Index + 2);

			float const t = Mu;
			float const t2 = Sq(t);
			float const t3 = t2*t;

			return ((P1 * 2.0) + (P0*-1.0 + P2) * t + (P0*2.0 - P1*5.0 + P2*4.0 - P3) * t2 + (P0*-1.0 + P1*3.0 - P2*3.0 + P3) * t3) * 0.5;
		}

	}
}
