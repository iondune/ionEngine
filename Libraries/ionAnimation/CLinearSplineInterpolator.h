
#pragma once

#include "ISplineInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CLinearSplineInterpolator : public ISplineInterpolator<T>
		{

		public:

			virtual T Interpolate(ISpline<T> const & Path, int const Index, float const Mu);

		};

		template <typename T>
		T CLinearSplineInterpolator<T>::Interpolate(ISpline<T> const & Path, int const Index, float const Mu)
		{
			return Path.GetNode(Index) * (1.f - Mu) + Path.GetNode(Index + 1) * Mu;
		}

	}
}
