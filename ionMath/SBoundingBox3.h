
#pragma once

#include "SVector3.h"
#include "SLine3.h"


template <typename T, typename Vector = SVector3<T> >
class SBoundingBox3
{

	typedef SBoundingBox3<T, Vector> Type;

public:

	Vector MinCorner, MaxCorner;

	SBoundingBox3()
	{}

	SBoundingBox3(Vector const & min, Vector const & max)
		: MinCorner(min), MaxCorner(max)
	{}

	explicit SBoundingBox3(Vector const & v)
		: MinCorner(v), MaxCorner(v)
	{}

	Vector const GetExtent() const
	{
		return MaxCorner - MinCorner;
	}

	Vector const GetCenter() const
	{
		return (MaxCorner + MinCorner) / 2;
	}

	bool IsPointInside(Vector const & p) const
	{
		return
			p.X >= MinCorner.X && p.X <= MaxCorner.X &&
			p.Y >= MinCorner.Y && p.Y <= MaxCorner.Y &&
			p.Z >= MinCorner.Z && p.Z <= MaxCorner.Z;
	}

	bool const Intersects(Type const & r) const
	{
		return (MaxCorner.Y > r.MinCorner.Y &&
			MinCorner.Y < r.MaxCorner.Y &&
			MaxCorner.X > r.MinCorner.X &&
			MinCorner.X < r.MaxCorner.X &&
			MaxCorner.Z > r.MinCorner.Z &&
			MinCorner.Z < r.MaxCorner.Z);
	}

	void AddInternalPoint(Vector const & v)
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

	void AddInternalBox(Type const & bb)
	{
		AddInternalPoint(bb.MaxCorner);
		AddInternalPoint(bb.MinCorner);
	}

	// These intersect methods direct copies from irrlicht engine
	bool IntersectsWithLine(SLine3<T, Vector> const & line) const
	{
		return IntersectsWithLine(line.GetMiddle(), line.GetVector().GetNormalized(), line.Length() * 0.5f);
	}

	// These intersect methods direct copies from irrlicht engine
	bool IntersectsWithLine(Vector const & linemiddle, Vector const & linevect, T halflength) const
	{
		const Vector e = GetExtent() * (T) 0.5;
		const Vector t = GetCenter() - linemiddle;

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

	T const GetMaximumRadius(Vector const Scale) const
	{
		Vector const Extents = GetExtent() / 2;
		return max((Extents*Scale).xy().length(), (Extents*Scale).xz().length(), (Extents*Scale).yz().length());
	}

	Vector const GetCorner(int const i) const
	{
		Vector const Center = GetCenter();
		Vector const Extent = GetExtent() / 2;

		switch (i)
		{
		default:
		case 0: return Vector(Center.X + Extent.X, Center.Y + Extent.Y, Center.Z + Extent.Z);
		case 1: return Vector(Center.X + Extent.X, Center.Y - Extent.Y, Center.Z + Extent.Z);
		case 2: return Vector(Center.X + Extent.X, Center.Y + Extent.Y, Center.Z - Extent.Z);
		case 3: return Vector(Center.X + Extent.X, Center.Y - Extent.Y, Center.Z - Extent.Z);
		case 4: return Vector(Center.X - Extent.X, Center.Y + Extent.Y, Center.Z + Extent.Z);
		case 5: return Vector(Center.X - Extent.X, Center.Y - Extent.Y, Center.Z + Extent.Z);
		case 6: return Vector(Center.X - Extent.X, Center.Y + Extent.Y, Center.Z - Extent.Z);
		case 7: return Vector(Center.X - Extent.X, Center.Y - Extent.Y, Center.Z - Extent.Z);
		};
	}

	void MoveTo(Vector const & Center)
	{
		Move(Center - GetCenter());
	}

	void Move(Vector const & Offset)
	{
		MinCorner += Offset;
		MaxCorner += Offset;
	}

	void Resize(Vector const & Size)
	{
		Vector const Center = GetCenter();
		MinCorner = Center - Size / 2;
		MaxCorner = Center + Size / 2;
	}

};

typedef SBoundingBox3<f32> SBoundingBox3f;
typedef SBoundingBox3<f64> SBoundingBox3d;
typedef SBoundingBox3<s32> SBoundingBox3i;
