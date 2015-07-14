
#pragma once

#include <ionCore.h>
#include <vector>

#include "IInterpolator.h"
#include "Interpolators.h"


template <typename TPathNode>
class CPath : public IPath<TPathNode>
{

protected:

	std::vector<TPathNode> Nodes;
	std::vector<f32> DistanceTable;
	f32 MuIncrement;
	bool Looping;

	mutable IInterpolator<TPathNode> * DefaultInterpolator;

public:

	CPath();

	std::vector<TPathNode> const & getNodes() const;
	std::vector<TPathNode> & getNodes();

	s32 const sanitizeIndex(s32 Index) const;
	s32 const getIndexFromMu(f32 const Mu) const;

	void addNode(TPathNode const & Node);

	bool const setLooping(bool const looping);
	bool const isLooping() const;

	IInterpolator<TPathNode> * setDefaultInterpolator(IInterpolator<TPathNode> * defaultInterpolator);
	IInterpolator<TPathNode> const * getDefaultInterpolator() const;

	TPathNode const & getNode(s32 const Index) const;
	TPathNode const getNodeInterpolated(f32 const Mu, IInterpolator<TPathNode> * Interpolator = 0) const;

	f32 const buildDistanceTable(f32 const Increment = 0.1f, IInterpolator<TPathNode> * Interpolator = 0);

	f32 const getMuFromArcLengthDistance(f32 const Distance, IInterpolator<TPathNode> * Interpolator = 0);
	TPathNode const getNodeArcLengthParametized(f32 const Distance, IInterpolator<TPathNode> * Interpolator = 0);
	int getNodeFromArcLengthParametized(f32 const Distance);

};

template <typename TPathNode>
s32 const CPath<TPathNode>::sanitizeIndex(s32 Index) const
{
	if (Looping)
	{
		// Negative indices
		while (Index < 0)
			Index += Nodes.size();

		// Indices > Path size
		if (Index >= static_cast<s32>(Nodes.size()))
			Index %= Nodes.size();
	}
	else
	{
		Index = Clamp<s32>(Index, 0, Nodes.size() - 1);
	}

	return Index;
}

template <typename TPathNode>
s32 const CPath<TPathNode>::getIndexFromMu(f32 const Mu) const
{
	return static_cast<s32>(floor(Mu) + RoundingError32);
}

template <typename TPathNode>
CPath<TPathNode>::CPath()
	: Looping(true), MuIncrement(0.f), DefaultInterpolator(new CLinearInterpolator<TPathNode>())
{}

template <typename TPathNode>
std::vector<TPathNode> const & CPath<TPathNode>::getNodes() const
{
	return Nodes;
}

template <typename TPathNode>
std::vector<TPathNode> & CPath<TPathNode>::getNodes()
{
	return Nodes;
}

template <typename TPathNode>
void CPath<TPathNode>::addNode(TPathNode const & Node)
{
	Nodes.push_back(Node);
	DistanceTable.clear();
}

template <typename TPathNode>
bool const CPath<TPathNode>::setLooping(bool const looping)
{
	DistanceTable.clear();
	return Looping = looping;
}

template <typename TPathNode>
bool const CPath<TPathNode>::isLooping() const
{
	return Looping;
}

template <typename TPathNode>
IInterpolator<TPathNode> * CPath<TPathNode>::setDefaultInterpolator(IInterpolator<TPathNode> * defaultInterpolator)
{
	if (DefaultInterpolator)
		delete DefaultInterpolator;
	return DefaultInterpolator = defaultInterpolator;
}

template <typename TPathNode>
IInterpolator<TPathNode> const * CPath<TPathNode>::getDefaultInterpolator() const
{
	return DefaultInterpolator;
}

template <typename TPathNode>
TPathNode const & CPath<TPathNode>::getNode(s32 const Index) const
{
	return Nodes[sanitizeIndex(Index)];
}

template <typename TPathNode>
TPathNode const CPath<TPathNode>::getNodeInterpolated(f32 const Mu, IInterpolator<TPathNode> * Interpolator) const
{
	if (! Interpolator)
		Interpolator = DefaultInterpolator;

	if (! Interpolator)
		return TPathNode();

	s32 const Index = sanitizeIndex(getIndexFromMu(Mu));

	return Interpolator->interpolate(* this, Index, fmodf(Mu, 1.f));
}

template <typename TPathNode>
f32 const CPath<TPathNode>::buildDistanceTable(f32 const Increment, IInterpolator<TPathNode> * Interpolator)
{
	if (! Interpolator)
		Interpolator = DefaultInterpolator;

	if (! Interpolator)
		return 0.f;

	DistanceTable.clear();
	MuIncrement = Increment;

	f32 const Max = static_cast<f32>(Looping ? Nodes.size() : Nodes.size() - 1);
	TPathNode Last = Interpolator->interpolate(* this, 0, 0.f);
	DistanceTable.push_back(0.f);

	for (f32 Mu = Increment;; Mu += Increment)
	{
		TPathNode Current = Interpolator->interpolate(* this, sanitizeIndex(getIndexFromMu(Mu)), fmodf(Mu, 1.f));
		DistanceTable.push_back((Current - Last).length() + (DistanceTable.size() ? DistanceTable.back() : 0.f));
		Last = Current;

		if (Mu > Max)
			break;
	}

	return DistanceTable.back();
}


template <typename TPathNode>
f32 const CPath<TPathNode>::getMuFromArcLengthDistance(f32 const Distance, IInterpolator<TPathNode> * Interpolator)
{
	if (DistanceTable.size() == 0)
		buildDistanceTable(0.1f, Interpolator);

	if (DistanceTable.size() == 0)
		return 0.f;

	u32 Max = DistanceTable.size() - 1, Min = 0;

	f32 const ModulatedDistance = fmodf(Distance, DistanceTable.back());

	while (Max > Min + 1)
	{
		u32 const Midpoint = (Max + Min) / 2;
		f32 const Value = DistanceTable[Midpoint];
		if (ModulatedDistance > Value)
			Min = Midpoint;
		else
			Max = Midpoint;
	}

	if (Max != Min + 1)
		std::cerr << "Unexpected values of Max and Min in getNodeArcLengthParametized(...): " << Min << " " << Max << std::endl;

	return (Min + (ModulatedDistance - DistanceTable[Min]) / (DistanceTable[Min+1] - DistanceTable[Min])) * MuIncrement;
}

template <typename TPathNode>
TPathNode const CPath<TPathNode>::getNodeArcLengthParametized(f32 const Distance, IInterpolator<TPathNode> * Interpolator)
{
	if (! Interpolator)
		Interpolator = DefaultInterpolator;

	if (! Interpolator)
		return TPathNode();

	f32 const Mu = getMuFromArcLengthDistance(Distance);
	s32 const Index = sanitizeIndex(getIndexFromMu(Mu));

	return Interpolator->interpolate(* this, Index, fmodf(Mu, 1.f));
}

template <typename TPathNode>
int CPath<TPathNode>::getNodeFromArcLengthParametized(f32 const Distance)
{
	f32 const Mu = getMuFromArcLengthDistance(Distance);
	s32 const Index = sanitizeIndex(getIndexFromMu(Mu));
	return Index;
}
