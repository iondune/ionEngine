
#pragma once

#include "SVector3.h"
#include "SLine3.h"


template <typename T, typename Vector = vec3<T> >
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

	Vector GetExtent() const
	{
		return MaxCorner - MinCorner;
	}

	Vector GetHalfExtent() const
	{
		return (MaxCorner - MinCorner) / 2;
	}

	Vector GetCenter() const
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

	bool Intersects(Type const & r) const
	{
		return (MaxCorner.Y >= r.MinCorner.Y &&
			MinCorner.Y <= r.MaxCorner.Y &&
			MaxCorner.X >= r.MinCorner.X &&
			MinCorner.X <= r.MaxCorner.X &&
			MaxCorner.Z >= r.MinCorner.Z &&
			MinCorner.Z <= r.MaxCorner.Z);
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

	// from http://www.codercorner.com/RayAABB.cpp
	bool IntersectsWithRay(vec3f const & origin, vec3f const & dir, vec3f & coord) const
	{
		static T const RAYAABB_EPSILON = RoundingError<T>::Value();
		bool Inside = true;
		vec3f const MinB = MinCorner;
		vec3f const MaxB = MaxCorner;
		vec3f MaxT;
		MaxT.X = MaxT.Y = MaxT.Z = -1;

		// Find candidate planes.
		for (uint i = 0; i<3; i++)
		{
			if (origin[i] < MinB[i])
			{
				coord[i] = MinB[i];
				Inside = false;

				// Calculate T distances to candidate planes
				if (((uint)(dir[i])))	MaxT[i] = (MinB[i] - origin[i]) / dir[i];
			}
			else if (origin[i] > MaxB[i])
			{
				coord[i] = MaxB[i];
				Inside = false;

				// Calculate T distances to candidate planes
				if (((uint)(dir[i])))	MaxT[i] = (MaxB[i] - origin[i]) / dir[i];
			}
		}

		// Ray origin inside bounding box
		if (Inside)
		{
			coord = origin;
			return true;
		}

		// Get largest of the maxT's for final choice of intersection
		uint WhichPlane = 0;
		if (MaxT[1] > MaxT[WhichPlane])	WhichPlane = 1;
		if (MaxT[2] > MaxT[WhichPlane])	WhichPlane = 2;

		// Check final candidate actually inside box
		if (((uint)(MaxT[WhichPlane])) & 0x80000000) return false;

		for (uint i = 0; i<3; i++)
		{
			if (i != WhichPlane)
			{
				coord[i] = origin[i] + MaxT[WhichPlane] * dir[i];
				if (coord[i] < MinB[i] - RAYAABB_EPSILON || coord[i] > MaxB[i] + RAYAABB_EPSILON)	return false;

			}
		}
		return true;	// ray hits box
	}

	bool IntersectsWithLimitedRay(vec3f const & origin, vec3f const & dir, vec3f & coord) const
	{
		if (IntersectsWithRay(origin, dir, coord))
		{
			return coord.GetDistanceSqFrom(origin) <= dir.LengthSq();
		}

		return false;
	}

	T const GetMaximumRadius(Vector const Scale) const
	{
		Vector const Extents = GetExtent() / 2;
		return max((Extents*Scale).xy().length(), (Extents*Scale).xz().length(), (Extents*Scale).yz().length());
	}

	Vector const GetCorner(int const i) const
	{
		switch (i)
		{
		default:
		case 0:
			return Vector(MinCorner.X, MinCorner.Y, MinCorner.Z);
		case 1:
			return Vector(MinCorner.X, MinCorner.Y, MaxCorner.Z);
		case 2:
			return Vector(MinCorner.X, MaxCorner.Y, MinCorner.Z);
		case 3:
			return Vector(MinCorner.X, MaxCorner.Y, MaxCorner.Z);
		case 4:
			return Vector(MaxCorner.X, MinCorner.Y, MinCorner.Z);
		case 5:
			return Vector(MaxCorner.X, MinCorner.Y, MaxCorner.Z);
		case 6:
			return Vector(MaxCorner.X, MaxCorner.Y, MinCorner.Z);
		case 7:
			return Vector(MaxCorner.X, MaxCorner.Y, MaxCorner.Z);
		}
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

	void Reset(Vector const & Point)
	{
		MinCorner = MaxCorner = Point;
	}

	void Transform(glm::mat4 const & Transformation)
	{
		std::vector<Vector> Vertices;
		for (int i = 0; i < 8; ++ i)
			Vertices.push_back(GetCorner(i));

		Reset(Vertices[0].GetTransformed(Transformation));
		for (int i = 0; i < 8; ++ i)
			AddInternalPoint(Vertices[i].GetTransformed(Transformation));
	}

};

template <typename T>
using boundingbox3 = SBoundingBox3<T>;

template <typename T>
using bbox3 = SBoundingBox3<T>;

template <typename T>
using box3 = SBoundingBox3<T>;

typedef SBoundingBox3<f32> SBoundingBox3f;
typedef SBoundingBox3<f64> SBoundingBox3d;
typedef SBoundingBox3<s32> SBoundingBox3i;

typedef SBoundingBox3<f32> box3f;
typedef SBoundingBox3<f64> box3d;
typedef SBoundingBox3<s32> box3i;
