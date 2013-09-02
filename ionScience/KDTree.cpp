#include "KDTree.h"

#include <functional>
#include <algorithm>


///////////////////////
// KDTreeNeighborSet //
///////////////////////

KDTreeNeighborSet::KDTreeNeighborSet(u32 const k, vec3f const & goal)
	: K(k), Goal(goal)
{}

void KDTreeNeighborSet::ConsiderPoint(vec3f const & Point)
{
	if (! Filled())
	{
		Set.push_back(std::make_pair(Point, Point.GetDistanceSqFrom(Goal)));
		std::sort(Set.begin(), Set.end(), [](std::pair<vec3f, f32> const & left, std::pair<vec3f, f32> const & right)
		{
			return left.second < right.second;
		});
	}
	else
	{
		f32 const Distance = Point.GetDistanceSqFrom(Goal);
		if (Distance < Set.back().second)
		{
			Set.erase(-- Set.end());
			Set.push_back(std::make_pair(Point, Distance));
			std::sort(Set.begin(), Set.end(), [](std::pair<vec3f, f32> const & left, std::pair<vec3f, f32> const & right)
			{
				return left.second < right.second;
			});
		}
	}
}

f32 KDTreeNeighborSet::GetWorstDistance() const
{
	return Set.back().second;
}

bool KDTreeNeighborSet::Filled() const
{
	return Set.size() == K;
}


////////////////
// KDTreeNode //
////////////////

void KDTreeNode::Split(vec3f * Elements, u32 const Count, s32 const Axis)
{
	static std::function<bool(vec3f, vec3f)> Comparators[] =
	{
		[](vec3f a, vec3f b) -> bool
		{
			return a.X < b.X;
		},
		[](vec3f a, vec3f b) -> bool
		{
			return a.Y < b.Y;
		},
		[](vec3f a, vec3f b) -> bool
		{
			return a.Z < b.Z;
		}
	};

	SplitAxis = Axis;

	std::sort(Elements, Elements + Count, Comparators[SplitAxis]);

	if (Count > 2)
	{
		u32 const Split = Count / 2;
		
		LeftSide = new KDTreeNode;
		LeftSide->Split(Elements, Split, (SplitAxis + 1) % 3);
		RightSide = new KDTreeNode;
		RightSide->Split(Elements + Split + 1, Count - Split - 1, (SplitAxis + 1) % 3);

		Position = Elements[Split]; 
	}
	else if (Count == 2)
	{
		LeftSide = new KDTreeNode;
		LeftSide->Split(Elements, 1, (SplitAxis + 1) % 3);

		Position = Elements[1];
	}
	else if (Count == 1)
	{
		Position = Elements[0];
	}
	else
	{
		std::cerr << "Unexpected condition! Attempting to split branch of 0 nodes." << std::endl;
	}
}

vec3f KDTreeNode::NearestNeighbor(vec3f const & Point) const
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

void KDTreeNode::NearestKNeighbors(KDTreeNeighborSet & Set) const
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

vec3f KDTree::NearestNeighbor(vec3f const & Point) const
{
	return Root->NearestNeighbor(Point);
}

KDTreeNeighborSet KDTree::NearestKNeighbors(vec3f const & Point, u32 const K) const
{
	KDTreeNeighborSet Set(K, Point);
	Root->NearestKNeighbors(Set);
	return Set;
}

void KDTree::Build(vec3f * Elements, u32 const Count)
{
	Root = new KDTreeNode;
	Root->Split(Elements, Count, 0);
}
