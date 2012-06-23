#ifndef _CABBAGE_CORE_SRECT2_H_INCLUDED_
#define _CABBAGE_CORE_SRECT2_H_INCLUDED_

#include "SVector2.h"
#include "ionUtils.h"

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

	SVector2<T> const otherCorner() const
	{
		return Position + Size;
	}

	SVector2<T> const getCenter() const
	{
		return Position + Size / 2.f;
	}

	bool const intersects(SRect2<T> const & r) const
	{
		return (otherCorner().Y > r.Position.Y || equals(otherCorner().Y, r.Position.Y) ) && 
			(Position.Y < r.otherCorner().Y || equals(Position.Y, r.otherCorner().Y) ) && 
			(otherCorner().X > r.Position.X || equals(otherCorner().X, r.Position.X) ) && 
			(Position.X < r.otherCorner().X || equals(Position.X, r.otherCorner().X) );
	}

	SRect2 const getIntersection(SRect2<T> const & r) const
	{
		SVector2<T> Position(std::max(r.Position.X, Position.X), std::max(r.Position.Y, Position.Y));
		SVector2<T> OtherCorner(std::min(r.otherCorner().X, otherCorner().X), std::min(r.otherCorner().Y, otherCorner().Y));

		return SRect2<T>(Position, OtherCorner - Position);
	}

	bool const isPointInside(SVector2<T> const & v) const
	{
		return (otherCorner().Y > v.Y && 
			Position.Y < v.Y && 
			otherCorner().X > v.X && 
			Position.X < v.X);
	}

	T const getArea() const
	{
		return Size.X * Size.Y;
	}

};

typedef SRect2<double> SRect2d;
typedef SRect2<float> SRect2f;
typedef SRect2<int> SRect2i;

#endif
