
#pragma once

#include <ionCore.h>
#include "SLine3.h"


namespace ion
{

	//! \brief 3D axis-aligned bounding box
	//! \ingroup ionMath
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

		static Type PositionSize(Vector const & position, Vector const & size)
		{
			return SBoundingBox3(position - size / 2, position + size / 2);
		}

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

		bool IntersectsWithRay(vec3f const & Origin, vec3f const & Direction, vec3f & coord) const
		{
			T tmin = -std::numeric_limits<T>::max();
			T tmax = std::numeric_limits<T>::max();

			for (int i = 0; i < 3; ++ i)
			{
				if (Direction[i] == 0)
				{
					if (Origin[i] <= MinCorner[i] || Origin[i] >= MaxCorner[i])
					{
						return false;
					}
				}
				else
				{
					T t1 = (MinCorner[i] - Origin[i]) / Direction[i];
					T t2 = (MaxCorner[i] - Origin[i]) / Direction[i];

					if (t1 > t2)
					{
						std::swap(t1, t2);
					}

					tmin = Max(t1, tmin);
					tmax = Min(t2, tmax);

					if (tmin > tmax)
					{
						return false;
					}
					if (tmax < 0)
					{
						return false;
					}
				}
			}

			if ((tmin > std::numeric_limits<T>::max()) || (tmax < 0))
			{
				return false;
			}

			if (tmin > 0)
			{
				coord = Origin + Direction * tmin;
			}
			else
			{
				coord = Origin + Direction * tmax;
			}
			return true;
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

	typedef SBoundingBox3<float> SBoundingBox3f;
	typedef SBoundingBox3<double> SBoundingBox3d;
	typedef SBoundingBox3<int> SBoundingBox3i;

	typedef SBoundingBox3<float> box3f;
	typedef SBoundingBox3<double> box3d;
	typedef SBoundingBox3<int> box3i;

}
