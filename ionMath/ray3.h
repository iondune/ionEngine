
#pragma once

#include "SVector3.h"


template <typename T>
class ray3
{

public:

	vec3<T> Origin;
	vec3<T> Direction;

	ray3()
	{
		this->Origin = vec3<T>(0);
		this->Direction = vec3<T>(0, 0, 1);
	}

	ray3(vec3<T> const & Origin, vec3<T> const & Direction)
	{
		this->Origin = Origin;
		this->Direction = Direction;
	}

	vec3<T> GetPoint(T const Parameter) const
	{
		return Origin + Parameter * Direction;
	}

	void Transform(glm::mat4 const & Matrix)
	{
		Origin.Transform(Matrix, 1);
		Direction.Transform(Matrix, 0);
	}

	ray3 GetTransformed(glm::mat4 const & Matrix) const
	{
		ray3 ret;
		ret.Origin = Origin.GetTransformed(Matrix, 1);
		ret.Direction = Direction.GetTransformed(Matrix, 0);
		return ret;
	}

#pragma warning(disable: 4723)
	bool IntersectsBox(box3<T> const & Box, T * Intersection = nullptr) const
	{
		T tmin = (Box.MinCorner.X - Origin.X) / Direction.X;
		T tmax = (Box.MaxCorner.X - Origin.X) / Direction.X;

		if (tmin > tmax)
			std::swap(tmin, tmax);

		T tymin = (Box.MinCorner.Y - Origin.Y) / Direction.Y;
		T tymax = (Box.MaxCorner.Y - Origin.Y) / Direction.Y;

		if (tymin > tymax)
			std::swap(tymin, tymax);

		if ((tmin > tymax) || (tymin > tmax))
			return false;

		if (tymin > tmin)
			tmin = tymin;
		if (tymax < tmax)
			tmax = tymax;

		T tzmin = (Box.MinCorner.Z - Origin.Z) / Direction.Z;
		T tzmax = (Box.MaxCorner.Z - Origin.Z) / Direction.Z;

		if (tzmin > tzmax)
			std::swap(tzmin, tzmax);

		if ((tmin > tzmax) || (tzmin > tmax))
			return false;

		if (tzmin > tmin)
			tmin = tzmin;
		if (tzmax < tmax)
			tmax = tzmax;

		if ((tmin > std::numeric_limits<T>::max()) || (tmax < 0))
			return false;

		if (Intersection)
		{
			*Intersection = tmin;
		}
		return true;
	}
#pragma warning(default: 4723)

	bool IntersectsSphere(vec3<T> const & Center, T const Radius, T * Intersection = nullptr) const
	{
		vec3<T> const OffsetOrigin = Origin - Center;
		T const A = Dot(Direction, Direction);
		T const B = Dot(Direction, OffsetOrigin);
		T const C = Dot(OffsetOrigin, OffsetOrigin) - Radius*Radius;

		T const Discriminant = B * B - A * C;

		if (Discriminant >= 0.f)
		{
			T Dividend;
			if (B < 0)
			{
				Dividend = -B + sqrt(Discriminant);
			}
			else
			{
				Dividend = -B - sqrt(Discriminant);
			}

			T Parameter = C / Dividend;

			if (Parameter <= 0)
			{
				Parameter = Dividend / A;
			}

			if (Parameter >= 0)
			{
				if (Intersection)
				{
					*Intersection = Parameter;
				}
				return true;
			}
		}

		return false;
	}

	bool operator == (ray3<T> const & other)
	{
		return Origin == other.Origin && Direction == other.Direction;
	}

	friend std::ostream & operator << (std::ostream & stream, ray3<T> const & ray)
	{
		return stream << "{" << ray.Origin << "} -> {" << ray.Direction << "}";
	}

};

typedef ray3<float> ray3f;
typedef ray3<double> ray3d;
