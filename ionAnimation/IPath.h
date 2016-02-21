
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Animation
	{

		template <typename TPathNode>
		class IInterpolator;

		template <typename TPathNode>
		class IPath
		{

		public:

			virtual vector<TPathNode> const & GetNodes() const = 0;
			virtual vector<TPathNode> & GetNodes() = 0;

			virtual void AddNode(TPathNode const & Node) = 0;

			virtual void SetLooping(bool const looping) = 0;
			virtual bool IsLooping() const = 0;

			virtual void SetDefaultInterpolator(SharedPtr<IInterpolator<TPathNode>> defaultInterpolator) = 0;
			virtual SharedPtr<IInterpolator<TPathNode>> GetDefaultInterpolator() const = 0;

			virtual int SanitizeIndex(int Index) const = 0;

			virtual TPathNode const & GetNode(int const Index) const = 0;
			virtual TPathNode GetNodeInterpolated(float const Intermediate, SharedPtr<IInterpolator<TPathNode>> Interpolator = nullptr) const = 0;

			virtual float BuildDistanceTable(float const Increment = 0.1f, SharedPtr<IInterpolator<TPathNode>> Interpolator = nullptr) = 0;
			virtual float GetIntermediateFromDistance(float const Distance, SharedPtr<IInterpolator<TPathNode>> Interpolator = nullptr) = 0;
			virtual TPathNode GetNodeFromDistance(float const Distance, SharedPtr<IInterpolator<TPathNode>> Interpolator = nullptr) = 0;

		};

	}
}
