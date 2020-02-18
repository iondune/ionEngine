
#pragma once

#include <ionCore.h>
#include "line2.h"


namespace ion
{

	template <typename T>
	struct box2
	{
		vec2<T> Min;
		vec2<T> Max;

		line2<T> GetEdge(int const i) const
		{
			switch (i % 4)
			{
			default:
			case 0:
				return line2<T>(
					vec2<T>(Min.X, Min.Y),
					vec2<T>(Min.X, Max.Y));
			case 1:
				return line2<T>(
					vec2<T>(Min.X, Min.Y),
					vec2<T>(Max.X, Min.Y));
			case 2:
				return line2<T>(
					vec2<T>(Max.X, Min.Y),
					vec2<T>(Max.X, Max.Y));
			case 3:
				return line2<T>(
					vec2<T>(Min.X, Max.Y),
					vec2<T>(Max.X, Max.Y));
			}
		}

		vec2<T> GetCorner(int const i) const
		{
			switch (i % 4)
			{
			default:
			case 0:
				return vec2<T>(Min.X, Min.Y);
			case 1:
				return vec2<T>(Min.X, Min.Y);
			case 2:
				return vec2<T>(Max.X, Min.Y);
			case 3:
				return vec2<T>(Min.X, Max.Y);
			}
		}

		bool IsPointInside(vec2<T> const & Point) const
		{
			return (Max.Y > Point.Y &&
				Min.Y < Point.Y &&
				Max.X > Point.X &&
				Min.X < Point.X);
		}

		void Reset(vec2<T> const & Point)
		{
			Min = Max = Point;
		}

		void AddPoint(vec2<T> const & Point)
		{
			Min.X = Minimum(Min.X, Point.X);
			Min.Y = Minimum(Min.Y, Point.Y);
			Max.X = Maximum(Max.X, Point.X);
			Max.Y = Maximum(Max.Y, Point.Y);
		}

		bool Intersects(box2<T> const & r) const
		{
			return
				Max.Y >= r.Min.Y &&
				Min.Y <= r.Max.Y &&
				Max.X >= r.Min.X &&
				Min.X <= r.Max.X;
		}

	};

	typedef box2<float> box2f;
	typedef box2<double> box2d;
	typedef box2<int> box2i;

}
