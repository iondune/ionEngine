
#pragma once

#include <ionCore.h>
#include "IPath.h"


namespace ion
{
	namespace Animation
	{

		template <typename TPathNode>
		class IInterpolator
		{

		public:

			virtual TPathNode const Interpolate(IPath<TPathNode> const & Path, int const Index, float const Mu) = 0;

		};

	}
}
