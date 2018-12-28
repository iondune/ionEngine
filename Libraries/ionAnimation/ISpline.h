
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Animation
	{
		
		template <typename TSplineNode>
		class ISpline
		{

		public:

			virtual vector<TSplineNode> const & GetNodes() const = 0;
			virtual vector<TSplineNode> & GetNodes() = 0;

			virtual bool IsLooping() const = 0;
			virtual int SanitizeIndex(int Index) const = 0;

			virtual TSplineNode const & GetNode(int const Index) const = 0;

		};

	}
}
