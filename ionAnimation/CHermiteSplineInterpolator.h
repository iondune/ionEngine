
#pragma once

#include <ionMath.h>
#include "ISplineInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CHermiteSplineInterpolator : public ISplineInterpolator<T>
		{

		public:

			virtual T Interpolate(ISpline<T> const & Path, int const Index, float const Mu);

		};

		template <typename T>
		T CHermiteSplineInterpolator<T>::Interpolate(ISpline<T> const & Path, int const Index, float const Mu)
		{
			T const P0 = Path.GetNode(Index + 0);
			T const P1 = Path.GetNode(Index + 1);

			vec3f const m0 = P0.Tangent;
			vec3f const m1 = P1.Tangent;
			float const t = Mu;
			float const t2 = t * t;
			float const t3 = t * t * t;

			return
				P0 * (2 * t3 - 3 * t2 + 1) +
				m0 * (t3 - 2 * t2 + t) +
				P1 * (-2 * t3 + 3 * t2) +
				m1 * (t3 - t2);
		}

	}
}
