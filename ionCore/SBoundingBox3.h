#ifndef _CABBAGE_CORE_SBOUNDINGBOX2_H_INCLUDED_
#define _CABBAGE_CORE_SBOUNDINGBOX2_H_INCLUDED_

#include "SVector3.h"
#include "SLine3.h"

template <typename T>
class SBoundingBox3
{

public:

	SVector3<T> MinCorner, MaxCorner;

	SBoundingBox3()
	{}

	SBoundingBox3(SVector3<T> const & min, SVector3<T> const & max)
		: MinCorner(min), MaxCorner(max)
	{}

	SBoundingBox3(SVector3<T> const & v)
		: MinCorner(v), MaxCorner(v)
	{}

	SVector3<T> const getExtent() const
	{
		return MaxCorner - MinCorner;
	}

	SVector3<T> const getCenter() const
	{
		return (MaxCorner + MinCorner) / 2;
	}

	bool isPointInside(SVector3<T> const & p) const
	{
		return 
			p.X >= MinCorner.X && p.X <= MaxCorner.X &&
			p.Y >= MinCorner.Y && p.Y <= MaxCorner.Y &&
			p.Z >= MinCorner.Z && p.Z <= MaxCorner.Z;
	}

	bool const intersects(SBoundingBox3<T> const & r) const
	{
		return (MaxCorner.Y > r.MinCorner.Y &&
			MinCorner.Y < r.MaxCorner.Y &&
			MaxCorner.X > r.MinCorner.X &&
			MinCorner.X < r.MaxCorner.X &&
			MaxCorner.Z > r.MinCorner.Z &&
			MinCorner.Z < r.MaxCorner.Z);
	}

	void addInternalPoint(SVector3<T> const & v)
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
	}

	void addInternalBox(SBoundingBox3<T> const & bb)
	{
		addInternalPoint(bb.MaxCorner);
		addInternalPoint(bb.MinCorner);
	}

	// These intersect methods direct copies from irrlicht engine
	bool intersectsWithLine(SLine3<T> const & line) const
	{
		return intersectsWithLine(line.getMiddle(), line.getVector().getNormalized(), line.length() * 0.5f);
	}

	// These intersect methods direct copies from irrlicht engine
	bool intersectsWithLine(SVector3<T> const & linemiddle, SVector3<T> const & linevect, T halflength) const
	{
		const SVector3<T> e = getExtent() * (T) 0.5;
		const SVector3<T> t = getCenter() - linemiddle;

		if ((fabs(t.X) > e.X + halflength * fabs(linevect.X)) ||
			(fabs(t.Y) > e.Y + halflength * fabs(linevect.Y)) ||
			(fabs(t.Z) > e.Z + halflength * fabs(linevect.Z)))
			return false;

		T r = e.Y * abs(linevect.Z) + e.Z * abs(linevect.Y);
		if (abs(t.Y*linevect.Z - t.Z*linevect.Y) > r)
			return false;

		r = e.X * abs(linevect.Z) + e.Z * abs(linevect.X);
		if (abs(t.Z*linevect.X - t.X*linevect.Z) > r)
			return false;

		r = e.X * abs(linevect.Y) + e.Y * abs(linevect.X);
		if (abs(t.X*linevect.Y - t.Y*linevect.X) > r)
			return false;

		return true;
	}

	T const getMaximumRadius(SVector3<T> const Scale) const
	{
		SVector3<T> const Extents = getExtent() / 2;
		return max((Extents*Scale).xy().length(), (Extents*Scale).xz().length(), (Extents*Scale).yz().length());
	}

	SVector3<T> const getCorner(int const i) const
	{
		SVector3<T> const Center = getCenter();
		SVector3<T> const Extent = getExtent() / 2;

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

typedef SBoundingBox3<float> SBoundingBox3f;
typedef SBoundingBox3<double> SBoundingBox3d;
typedef SBoundingBox3<int> SBoundingBox3i;

#endif
