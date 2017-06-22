
#pragma once

#include <ionCore.h>


namespace ion
{

	//! \brief 3D ray
	//! \ingroup ionMath
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
		bool IntersectsBox(box3<T> const & Box, T * Intersection) const
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
				if (tmin > 0)
				{
					*Intersection = tmin;
				}
				else
				{
					*Intersection = tmax;
				}
			}
			return true;
		}
#pragma warning(default: 4723)

#pragma warning(disable: 4723)
		bool IntersectsBox(box3<T> const & Box) const
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

		bool IntersectsTriangle(vec3f const & v0, vec3f const & v1, vec3f const & v2, T * Intersection) const
		{
			vec3f const p = Origin;
			vec3f const d = Direction;

			vec3f e1, e2, h, s, q;

			float a, f, u, v;
			e1 = v1 - v0;
			e2 = v2 - v0;

			h = Cross(d, e2);
			a = Dot(e1, h);

			if (a > -RoundingError32 && a < RoundingError32)
				return false;

			f = 1 / a;
			s = p - v0;
			u = f * (Dot(s, h));

			if ((u < 0.f || u > 1.f) && ! Equals(u, 0.f) && ! Equals(u, 1.f))
				return false;

			q = Cross(s, e1);
			v = f * Dot(d, q);

			if ((v < 0.f || u + v > 1.f) && ! Equals(v, 0.f) && ! Equals(u + v, 1.f))
				return false;

			float const t = f * Dot(e2, q);

			if (t >= 0.f || Equals(t, 0.f))
			{
				if (Intersection)
				{
					*Intersection = t;
				}

				return true;
			}
			else
				return false;
		}

		bool operator == (ray3<T> const & other) const
		{
			return Origin == other.Origin && Direction == other.Direction;
		}

		bool operator != (ray3<T> const & other) const
		{
			return Origin != other.Origin && Direction != other.Direction;
		}

		friend std::ostream & operator << (std::ostream & stream, ray3<T> const & ray)
		{
			return stream << "{" << ray.Origin << "} -> {" << ray.Direction << "}";
		}

	};

	typedef ray3<float> ray3f;
	typedef ray3<double> ray3d;

}
