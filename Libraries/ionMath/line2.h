
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

		vec2<T> GetNormal() const
		{
			return (End - Start).Rotate90CW().GetNormalized();
		}

		T Length() const
		{
			return Distance(Start, End);
		}

		friend T Length(line2<T> const & Line)
		{
			return Distance(Line.Start, Line.End);
		}

		vec2<T> const ClosestPointTo(vec2<T> const & Point) const
		{
			if (End == Start)
			{
				return LengthSq(Point - Start);
			}

			float const t = Clamp(Dot(Point - Start, End - Start) / LengthSq(End - Start), 0.f, 1.f);
			return Start + t * (End - Start);
		}

		float GetDistanceFrom(vec2<T> const & Point) const
		{
			return Distance(Point, ClosestPointTo(Point));
		}

		float GetDistanceSqFrom(vec2<T> const & Point) const
		{
			return DistanceSq(Point, ClosestPointTo(Point));
		}

		bool IntersectsWith(line2<T> const & Other, vec2<T> & Intersection) const
		{
			// Implementation adapted from Paul Bourke's intersection code
			// http://paulbourke.net/geometry/pointlineplane/
			// http://paulbourke.net/geometry/pointlineplane/pdb.c

			T const denom =  (Other.End.Y - Other.Start.Y) * (End.X   - Start.X)       - (Other.End.X - Other.Start.X) * (End.Y   - Start.Y);
			T const numera = (Other.End.X - Other.Start.X) * (Start.Y - Other.Start.Y) - (Other.End.Y - Other.Start.Y) * (Start.X - Other.Start.X);
			T const numerb = (End.X       - Start.X)       * (Start.Y - Other.Start.Y) - (End.Y       - Start.Y)       * (Start.X - Other.Start.X);

			// Are the line coincident?
			if (Equals(numera, (T) 0) && Equals(numerb, (T) 0) && Equals(denom, (T) 0))
			{
				Intersection = (Start + End) / 2;
				return true;
			}

			// Are the lines parallel?
			if (Equals(denom, (T) 0))
			{
				return false;
			}

			// Is the intersection along the the segments?
			T const mua = numera / denom;
			T const mub = numerb / denom;

			if (mua < 0 || mua > 1 || mub < 0 || mub > 1)
			{
				return false;
			}

			Intersection = Start + mua * (End - Start);
			return true;
		}

		float GetDistanceFrom(line2<T> const & Other) const
		{
			vec2<T> Intersect;

			if (IntersectsWith(Other, Intersect))
			{
				return 0.f;
			}

			return Min(GetDistanceFrom(Other.Start), GetDistanceFrom(Other.End), Other.GetDistanceFrom(Start), Other.GetDistanceFrom(End));
		}

		float GetDistanceSqFrom(line2<T> const & Other) const
		{
			vec2<T> Intersect;

			if (IntersectsWith(Other, Intersect))
			{
				return 0.f;
			}

			return Min(GetDistanceSqFrom(Other.Start), GetDistanceSqFrom(Other.End), Other.GetDistanceSqFrom(Start), Other.GetDistanceSqFrom(End));
		}

	};

	typedef line2<float> line2f;
	typedef line2<double> line2d;
	typedef line2<int> line2i;

}
