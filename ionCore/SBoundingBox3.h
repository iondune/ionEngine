#ifndef _CABBAGE_CORE_SBOUNDINGBOX2_H_INCLUDED_
#define _CABBAGE_CORE_SBOUNDINGBOX2_H_INCLUDED_

#include "SVector3.h"
#include "SLine3.h"

class SBoundingBox3
{
private:
	// A skeleton point is one that doesn't represent the box, but represents the innermose bounding box this box can be. Used for the spatial data structure
	SVector3f MinSkeletonPoint, MaxSkeletonPoint;

public:

	SVector3f MinCorner, MaxCorner;

	SBoundingBox3() :
		MinSkeletonPoint(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()),
		MaxSkeletonPoint(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity())
	{}

	SBoundingBox3(SVector3f const & min, SVector3f const & max)
		: MinCorner(min), MaxCorner(max),
		MinSkeletonPoint(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()),
		MaxSkeletonPoint(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity())
	{}

	SBoundingBox3(SVector3f const & v)
		: MinCorner(v), MaxCorner(v), 
		MinSkeletonPoint(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()),
		MaxSkeletonPoint(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity())
	{}

	SVector3f const getExtent() const
	{
		return MaxCorner - MinCorner;
	}

	SVector3f const getCenter() const
	{
		return (MaxCorner + MinCorner) / 2.f;
	}

	bool isPointInside(SVector3f const & p) const
	{
		return 
			p.X >= MinCorner.X && p.X <= MaxCorner.X &&
			p.Y >= MinCorner.Y && p.Y <= MaxCorner.Y &&
			p.Z >= MinCorner.Z && p.Z <= MaxCorner.Z;
	}

	bool const intersects(SBoundingBox3 const & r) const
	{
		return (MaxCorner.Y > r.MinCorner.Y &&
			MinCorner.Y < r.MaxCorner.Y &&
			MaxCorner.X > r.MinCorner.X &&
			MinCorner.X < r.MaxCorner.X &&
			MaxCorner.Z > r.MinCorner.Z &&
			MinCorner.Z < r.MaxCorner.Z);
	}

	void addInternalPoint(SVector3f const & v)
	{
		if (v.X > MaxCorner.X)
			MaxCorner.X = v.X;
		if (v.Y > MaxCorner.Y)
			MaxCorner.Y = v.Y;
		if (v.Z > MaxCorner.Z)
			MaxCorner.Z = v.Z;

		if (v.X < MinCorner.X)
			MinCorner.X = v.X;
		if (v.Y < MinCorner.Y)
			MinCorner.Y = v.Y;
		if (v.Z < MinCorner.Z)
			MinCorner.Z = v.Z;

		// Skeleton points just keep track of the smallest/biggest points
		if (v.X > MaxSkeletonPoint.X)
			MaxSkeletonPoint.X = v.X;
		if (v.Y > MaxSkeletonPoint.Y)
			MaxSkeletonPoint.Y = v.Y;
		if (v.Z > MaxSkeletonPoint.Z)
			MaxSkeletonPoint.Z = v.Z;

		if (v.X < MinSkeletonPoint.X)
			MinSkeletonPoint.X = v.X;
		if (v.Y < MinSkeletonPoint.Y)
			MinSkeletonPoint.Y = v.Y;
		if (v.Z < MinSkeletonPoint.Z)
			MinSkeletonPoint.Z = v.Z;
	}

	void shrink() {
		float const INF = std::numeric_limits<float>::infinity();

		// Make sure at least two points have been placed as internal points before allowing the bounding box to be shrunk
		assert((MinSkeletonPoint.X != INF && MinSkeletonPoint.Y != INF && MinSkeletonPoint.Z != INF) &&
			(MaxSkeletonPoint.X != -INF && MaxSkeletonPoint.Y != -INF && MaxSkeletonPoint.Z != -INF));
		assert(MinSkeletonPoint.X != MaxSkeletonPoint.X &&
			MinSkeletonPoint.Y != MaxSkeletonPoint.Y && 
			MinSkeletonPoint.Z != MaxSkeletonPoint.Z);

		MinCorner = MinSkeletonPoint;
		MaxCorner = MaxSkeletonPoint;
	}

	void addInternalBox(SBoundingBox3 const & bb)
	{
		addInternalPoint(bb.MaxCorner);
		addInternalPoint(bb.MinCorner);
	}

	// These intersect methods direct copies from irrlicht engine
	bool intersectsWithLine(SLine3 const & line) const
	{
		return intersectsWithLine(line.getMiddle(), line.getVector().getNormalized(), line.length() * 0.5f);
	}

	// These intersect methods direct copies from irrlicht engine
	bool intersectsWithLine(SVector3f const & linemiddle, SVector3f const & linevect, float halflength) const
	{
		const SVector3f e = getExtent() * 0.5f;
		const SVector3f t = getCenter() - linemiddle;

		if ((fabs(t.X) > e.X + halflength * fabs(linevect.X)) ||
			(fabs(t.Y) > e.Y + halflength * fabs(linevect.Y)) ||
			(fabs(t.Z) > e.Z + halflength * fabs(linevect.Z)))
			return false;

		float r = e.Y * fabs(linevect.Z) + e.Z * fabs(linevect.Y);
		if (fabs(t.Y*linevect.Z - t.Z*linevect.Y) > r)
			return false;

		r = e.X * fabs(linevect.Z) + e.Z * fabs(linevect.X);
		if (fabs(t.Z*linevect.X - t.X*linevect.Z) > r)
			return false;

		r = e.X * fabs(linevect.Y) + e.Y * fabs(linevect.X);
		if (fabs(t.X*linevect.Y - t.Y*linevect.X) > r)
			return false;

		return true;
	}

	float const getMaximumRadius(SVector3f const Scale) const
	{
		SVector3f const Extents = getExtent() / 2.f;
		return std::max(std::max((Extents*Scale).xy().length(), (Extents*Scale).xz().length()), (Extents*Scale).yz().length());
	}

	SVector3f const getCorner(int const i) const
	{
		SVector3f const Center = getCenter();
		SVector3f const Extent = getExtent() / 2.f;

		switch (i)
		{
		default: 
		case 0: return SVector3f(Center.X + Extent.X, Center.Y + Extent.Y, Center.Z + Extent.Z);
		case 1: return SVector3f(Center.X + Extent.X, Center.Y - Extent.Y, Center.Z + Extent.Z);
		case 2: return SVector3f(Center.X + Extent.X, Center.Y + Extent.Y, Center.Z - Extent.Z);
		case 3: return SVector3f(Center.X + Extent.X, Center.Y - Extent.Y, Center.Z - Extent.Z);
		case 4: return SVector3f(Center.X - Extent.X, Center.Y + Extent.Y, Center.Z + Extent.Z);
		case 5: return SVector3f(Center.X - Extent.X, Center.Y - Extent.Y, Center.Z + Extent.Z);
		case 6: return SVector3f(Center.X - Extent.X, Center.Y + Extent.Y, Center.Z - Extent.Z);
		case 7: return SVector3f(Center.X - Extent.X, Center.Y - Extent.Y, Center.Z - Extent.Z);
		};
	}

};

#endif
