
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Animation
	{
		
		template <typename TPathNode>
		class IPath
		{

		public:

			virtual vector<TPathNode> const & GetNodes() const = 0;
			virtual vector<TPathNode> & GetNodes() = 0;

			virtual bool IsLooping() const = 0;
			virtual int SanitizeIndex(int Index) const = 0;

			virtual TPathNode const & GetNode(int const Index) const = 0;

		};

	}
}
