
#pragma once

#include <ionCore.h>
#include <vector>


template <typename TPathNode>
class IInterpolator;

template <typename TPathNode>
class IPath
{

public:

	virtual s32 const sanitizeIndex(s32 Index) const = 0;
	virtual s32 const getIndexFromMu(f32 const Mu) const = 0;

	virtual std::vector<TPathNode> const & getNodes() const = 0;
	virtual std::vector<TPathNode> & getNodes() = 0;

	virtual void addNode(TPathNode const & Node) = 0;

	virtual bool const setLooping(bool const looping) = 0;
	virtual bool const isLooping() const = 0;

	virtual IInterpolator<TPathNode> * setDefaultInterpolator(IInterpolator<TPathNode> * defaultInterpolator) = 0;
	virtual IInterpolator<TPathNode> const * getDefaultInterpolator() const = 0;

	virtual TPathNode const & getNode(s32 const Index) const = 0;
	virtual TPathNode const getNodeInterpolated(f32 const Mu, IInterpolator<TPathNode> * Interpolator = 0) const = 0;

	virtual f32 const buildDistanceTable(f32 const Increment = 0.1f, IInterpolator<TPathNode> * Interpolator = 0) = 0;

	virtual f32 const getMuFromArcLengthDistance(f32 const Distance, IInterpolator<TPathNode> * Interpolator = 0) = 0;
	virtual TPathNode const getNodeArcLengthParametized(f32 const Distance, IInterpolator<TPathNode> * Interpolator = 0) = 0;

};
