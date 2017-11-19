
#pragma once

#include <ionMath.h>


namespace ion
{

	struct CKDTreeNeighborSet
	{
		int const K;
		vec3f const Goal;

		std::vector<std::pair<vec3f, float> > Set;

		CKDTreeNeighborSet(int const k, vec3f const & goal);

		void ConsiderPoint(vec3f const & Point);
		float GetWorstDistance() const;
		bool Filled() const;
	};

	class CKDTreeNode
	{

	public:

		CKDTreeNode * LeftSide = nullptr;
		CKDTreeNode * RightSide = nullptr;

		int SplitAxis = -1;
		vec3f Position;

		void Split(vec3f * Elements, int const Count, int const Axis);
		vec3f NearestNeighbor(vec3f const & Point) const;
		void NearestKNeighbors(CKDTreeNeighborSet & Set) const;

	};

	class CKDTree
	{

	public:

		void Build(vec3f * Elements, int const Count);
		vec3f NearestNeighbor(vec3f const & Point) const;
		CKDTreeNeighborSet NearestKNeighbors(vec3f const & Point, int const K) const;

		CKDTreeNode * Root = nullptr;

	};

}
