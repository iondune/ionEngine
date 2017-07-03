
#pragma once

#include <ionCore.h>


namespace ion
{

	//! \brief 2D line segment
	//! \ingroup ionMath
	template <typename T>
	class line2
	{

	public:

		vec2<T> Start;
		vec2<T> End;

		line2(vec2<T> const & start, vec2<T> const & end)
			: Start(start), End(end)
		{}

		vec2<T> GetMiddle() const
		{
			return (Start + End) / 2;
		}

		vec2<T> GetVector() const
		{
			return End - Start;
		}

		T Length() const
		{
			return Distance(Start, End);
		}

		friend T Length(line2<T> const & Line)
		{
			return Distance(Line.Start, Line.End);
		}

		vec2<T> const ClosestPointTo(vec2<T> const & Point)
		{
			if (End == Start)
			{
				return LengthSq(Point - Start);
			}

			float const t = Clamp(Dot(Point - Start, End - Start) / LengthSq(End - Start), 0.f, 1.f);
			return Start + t * (End - Start);
		}

		float GetDistanceFrom(vec2<T> const & Point)
		{
			return Distance(Point, ClosestPointTo(Point));
		}

		float GetDistanceSqFrom(vec2<T> const & Point)
		{
			return DistanceSq(Point, ClosestPointTo(Point));
		}

	};

	typedef line2<float> line2f;
	typedef line2<double> line2d;
	typedef line2<int> line2i;

}
