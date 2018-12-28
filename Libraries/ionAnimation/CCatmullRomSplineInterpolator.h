
#pragma once

#include "ISplineInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CCatmullRomSplineInterpolator : public ISplineInterpolator<T>
		{

		public:

			virtual T Interpolate(ISpline<T> const & Path, int const Index, float const Mu);

		};

		template <typename T>
		T CCatmullRomSplineInterpolator<T>::Interpolate(ISpline<T> const & Path, int const Index, float const Mu)
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
