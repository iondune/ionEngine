
#pragma once

#include "SVector2.h"


template <typename T>
class SRect2
{

public:

	SVector2<T> Position, Size;

	SRect2()
	{}

	SRect2(SVector2<T> const & position, SVector2<T> const & size)
		: Position(position), Size(size)
	{}

	SRect2(T const x, T const y, T const w, T const h)
		: Position(x, y), Size(w, h)
	{}

	SVector2<T> OtherCorner() const
	{
		return Position + Size;
	}

	SVector2<T> GetCenter() const
	{
		return Position + Size / 2;
	}

	bool Intersects(SRect2<T> const & r) const
	{
		return (OtherCorner().Y > r.Position.Y || Equals(OtherCorner().Y, r.Position.Y) ) &&
			(Position.Y < r.OtherCorner().Y || Equals(Position.Y, r.OtherCorner().Y) ) &&
			(OtherCorner().X > r.Position.X || Equals(OtherCorner().X, r.Position.X) ) &&
			(Position.X < r.OtherCorner().X || Equals(Position.X, r.OtherCorner().X) );
	}

	SRect2 GetIntersection(SRect2<T> const & r) const
	{
		SVector2<T> Position(std::max(r.Position.X, Position.X), std::max(r.Position.Y, Position.Y));
		SVector2<T> Corner(std::min(r.OtherCorner().X, OtherCorner().X), std::min(r.OtherCorner().Y, OtherCorner().Y));

		return SRect2<T>(Position, Corner - Position);
	}

	bool IsPointInside(SVector2<T> const & v) const
	{
		return (OtherCorner().Y > v.Y &&
			Position.Y < v.Y &&
			OtherCorner().X > v.X &&
			Position.X < v.X);
	}

	bool IsPointInsideOrOn(SVector2<T> const & v) const
	{
		return (OtherCorner().Y >= v.Y &&
			Position.Y <= v.Y &&
			OtherCorner().X >= v.X &&
			Position.X <= v.X);
	}

	T GetArea() const
	{
		return Size.X * Size.Y;
	}

	void Bounds(SVector2<T> const & pos1, SVector2<T> const & pos2)
	{
		Position = pos1;
		Size = pos2 - Position;
		if (Size.X < 0)
		{
			Position.X += Size.X;
			Size.X *= -1;
		}
		if (Size.Y < 0)
		{
			Position.Y += Size.Y;
			Size.Y *= -1;
		}
	}

	void ClipTo(SRect2 const & r)
	{
		SVector2<T> UpperLeftCorner = Position;
		SVector2<T> LowerRightCorner = OtherCorner();
		SVector2<T> const otherUpperLeftCorner = r.Position;
		SVector2<T> const otherLowerRightCorner = r.OtherCorner();

		if (otherLowerRightCorner.X < LowerRightCorner.X)
			LowerRightCorner.X = otherLowerRightCorner.X;
		if (otherLowerRightCorner.Y < LowerRightCorner.Y)
			LowerRightCorner.Y = otherLowerRightCorner.Y;

		if (otherUpperLeftCorner.X > UpperLeftCorner.X)
			UpperLeftCorner.X = otherUpperLeftCorner.X;
		if (otherUpperLeftCorner.Y > UpperLeftCorner.Y)
			UpperLeftCorner.Y = otherUpperLeftCorner.Y;

		// correct possible invalid rect resulting from clipping
		if (UpperLeftCorner.Y > LowerRightCorner.Y)
			UpperLeftCorner.Y = LowerRightCorner.Y;
		if (UpperLeftCorner.X > LowerRightCorner.X)
			UpperLeftCorner.X = LowerRightCorner.X;

		Position = UpperLeftCorner;
		Size = LowerRightCorner - UpperLeftCorner;
	}

};

typedef SRect2<f32> SRect2f;
typedef SRect2<f64> SRect2d;
typedef SRect2<s32> SRect2i;
typedef SRect2<u32> SRect2u;

typedef SRect2f rect2f;
typedef SRect2d rect2d;
typedef SRect2i rect2i;
typedef SRect2u rect2u;
