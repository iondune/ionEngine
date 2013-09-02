#pragma once

#include <ionTypes.h>
#include <ionMath.h>

#include <vector>


struct KDTreeNeighborSet
{
	u32 const K;
	vec3f const Goal;

	std::vector<std::pair<vec3f, f32> > Set;

	KDTreeNeighborSet(u32 const k, vec3f const & goal);

	void ConsiderPoint(vec3f const & Point);
	f32 GetWorstDistance() const;
	bool Filled() const;
};

class KDTreeNode
{

public:

	KDTreeNode()
		: LeftSide(), RightSide()
	{}

	KDTreeNode * LeftSide, * RightSide;
	s32 SplitAxis;
	vec3f Position;

	void Split(vec3f * Elements, u32 const Count, s32 const Axis);
	vec3f NearestNeighbor(vec3f const & Point) const;
	void NearestKNeighbors(KDTreeNeighborSet & Set) const;

};

class KDTree
{

public:

	KDTree()
		: Root()
	{}

	void Build(vec3f * Elements, u32 const Count);
	vec3f NearestNeighbor(vec3f const & Point) const;
	KDTreeNeighborSet NearestKNeighbors(vec3f const & Point, u32 const K) const;

	KDTreeNode * Root;

};
