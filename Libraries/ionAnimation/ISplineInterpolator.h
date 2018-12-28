
#pragma once

#include <ionCore.h>
#include "ISpline.h"


namespace ion
{
	namespace Animation
	{

		template <typename TSplineNode>
		class ISplineInterpolator
		{

		public:

			virtual TSplineNode Interpolate(ISpline<TSplineNode> const & Path, int const Index, float const Mu) = 0;

		};

	}
}
