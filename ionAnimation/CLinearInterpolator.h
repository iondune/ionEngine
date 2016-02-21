
#pragma once

#include "IInterpolator.h"


namespace ion
{
	namespace Animation
	{

		template <typename T>
		class CLinearInterpolator : public IInterpolator<T>
		{

		public:

			virtual T const Interpolate(IPath<T> const & Path, s32 const Index, float const Mu);

		};

		template <typename T>
		T const CLinearInterpolator<T>::Interpolate(IPath<T> const & Path, s32 const Index, float const Mu)
		{
			return Path.GetNode(Index) * (1.f - Mu) + Path.GetNode(Index + 1) * Mu;
		}

	}
}
