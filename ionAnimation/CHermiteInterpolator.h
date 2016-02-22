
#pragma once

#include <ionMath.h>
#include "IInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CHermiteInterpolator : public IInterpolator<T>
		{

		public:

			virtual T const Interpolate(IPath<T> const & Path, int const Index, float const Mu);

		};

		template <typename T>
		T const CHermiteInterpolator<T>::Interpolate(IPath<T> const & Path, int const Index, float const Mu)
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
