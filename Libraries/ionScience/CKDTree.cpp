
#include "CKDTree.h"

#include <functional>
#include <algorithm>


namespace ion
{

	////////////////////////
	// CKDTreeNeighborSet //
	////////////////////////

	CKDTreeNeighborSet::CKDTreeNeighborSet(int const k, vec3f const & goal)
		: K(k), Goal(goal)
	{}

	void CKDTreeNeighborSet::ConsiderPoint(vec3f const & Point)
	{
		if (! Filled())
		{
			Set.push_back(std::make_pair(Point, Point.GetDistanceSqFrom(Goal)));
			std::sort(Set.begin(), Set.end(), [](std::pair<vec3f, float> const & left, std::pair<vec3f, float> const & right)
			{
				return left.second < right.second;
			});
		}
		else
		{
			float const Distance = Point.GetDistanceSqFrom(Goal);
			if (Distance < Set.back().second)
			{
				Set.erase(-- Set.end());
				Set.push_back(std::make_pair(Point, Distance));
				std::sort(Set.begin(), Set.end(), [](std::pair<vec3f, float> const & left, std::pair<vec3f, float> const & right)
				{
					return left.second < right.second;
				});
			}
		}
	}

	float CKDTreeNeighborSet::GetWorstDistance() const
	{
		return Set.back().second;
	}

	bool CKDTreeNeighborSet::Filled() const
	{
		return Set.size() == K;
	}


	/////////////////
	// SKDTreeNode //
	/////////////////

	void CKDTreeNode::Split(vec3f * Elements, int const Count, int const Axis)
	{
		struct Sorter
		{
			static bool ByX(vec3f const & a, vec3f const & b)
			{
				return a.X < b.X;
			}
			static bool ByY(vec3f const & a, vec3f const & b)
			{
				return a.Y < b.Y;
			}
			static bool ByZ(vec3f const & a, vec3f const & b)
			{
				return a.Z < b.Z;
			}
		};

		bool (*Comparators[3])(vec3f const &, vec3f const &) =
		{
			Sorter::ByX,
			Sorter::ByY,
			Sorter::ByZ
		};

		SplitAxis = Axis;

		std::sort(Elements, Elements + Count, Comparators[SplitAxis]);

		if (Count > 2)
		{
			int const Split = Count / 2;

			LeftSide = new CKDTreeNode;
			LeftSide->Split(Elements, Split, (SplitAxis + 1) % 3);
			RightSide = new CKDTreeNode;
			RightSide->Split(Elements + Split + 1, Count - Split - 1, (SplitAxis + 1) % 3);

			Position = Elements[Split];
		}
		else if (Count == 2)
		{
			LeftSide = new CKDTreeNode;
			LeftSide->Split(Elements, 1, (SplitAxis + 1) % 3);

			Position = Elements[1];
		}
		else if (Count == 1)
		{
			Position = Elements[0];
		}
		else
		{
			Log::Error("Unexpected condition! Attempting to split branch of 0 nodes.");
		}
	}

	vec3f CKDTreeNode::NearestNeighbor(vec3f const & Point) const
	{
		if (! LeftSide && ! RightSide)
			return Position;

		vec3f CurrentBest = LeftSide->NearestNeighbor(Point);

		if (Position.GetDistanceSqFrom(Point) < CurrentBest.GetDistanceSqFrom(Point))
			CurrentBest = Position;

		if (RightSide && Sq(Position[SplitAxis] - Point[SplitAxis]) < CurrentBest.GetDistanceSqFrom(Point))
		{
			vec3f CandidateBest = RightSide->NearestNeighbor(Point);
			if (CandidateBest.GetDistanceSqFrom(Point) < CurrentBest.GetDistanceSqFrom(Point))
				CurrentBest = CandidateBest;
		}

		return CurrentBest;
	}

	void CKDTreeNode::NearestKNeighbors(CKDTreeNeighborSet & Set) const
	{
		Set.ConsiderPoint(Position);

		if (! LeftSide && ! RightSide)
			return;

		LeftSide->NearestKNeighbors(Set);

		if (RightSide && (Sq(Position[SplitAxis] - Set.Goal[SplitAxis]) < Set.GetWorstDistance() || ! Set.Filled()))
			RightSide->NearestKNeighbors(Set);
	}


	////////////
	// KDTree //
	////////////

	vec3f CKDTree::NearestNeighbor(vec3f const & Point) const
	{
		return Root->NearestNeighbor(Point);
	}

	CKDTreeNeighborSet CKDTree::NearestKNeighbors(vec3f const & Point, int const K) const
	{
		CKDTreeNeighborSet Set(K, Point);
		Root->NearestKNeighbors(Set);
		return Set;
	}

	void CKDTree::Build(vec3f * Elements, int const Count)
	{
		Root = new CKDTreeNode;
		Root->Split(Elements, Count, 0);
	}

}
