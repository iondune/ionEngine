
#pragma once

#include <ionMath.h>
#include "Interpolation.h"


namespace ion
{

	template <typename T>
	struct SVolume
	{
		vector<T> Values;
		vec3i Dimensions;

		SVolume(vec3i const & dimensions = vec3i())
			: Dimensions(dimensions), Values()
		{
			Allocate();
		}

		SVolume(T const & init, vec3i const & dimensions = vec3i())
			: Dimensions(dimensions), Values()
		{
			Allocate(init);
		}

		virtual void Allocate()
		{
			Values.resize(Dimensions.X * Dimensions.Y * Dimensions.Z);
		}

		virtual void Allocate(T const & value)
		{
			Values.resize(Dimensions.X * Dimensions.Y * Dimensions.Z, value);
		}

		virtual bool const InBounds(vec3i const Index) const
		{
			return InBounds(Index.X, Index.Y, Index.Z);
		}

		virtual bool const InBounds(int const X, int const Y, int const Z) const
		{
			return X >= 0 && X < Dimensions.X &&
				Y >= 0 && Y < Dimensions.Y &&
				Z >= 0 && Z < Dimensions.Z;
		}

		virtual T & Get(vec3i const Index)
		{
			return Get(Index.X, Index.Y, Index.Z);
		}

		virtual T const & Get(vec3i const Index) const
		{
			return Get(Index.X, Index.Y, Index.Z);
		}

		virtual T & Get(int const X, int const Y, int const Z)
		{
			int const Index = Clamp(X, 0, Dimensions.X - 1) + Dimensions.X * Clamp(Y, 0, Dimensions.Y - 1) + Dimensions.X * Dimensions.Y * Clamp(Z, 0, Dimensions.Z - 1);
			return Values[Index];
		}

		virtual T const & Get(int const X, int const Y, int const Z) const
		{
			int const Index = Clamp(X, 0, Dimensions.X - 1) + Dimensions.X * Clamp(Y, 0, Dimensions.Y - 1) + Dimensions.X * Dimensions.Y * Clamp(Z, 0, Dimensions.Z - 1);
			return Values[Index];
		}

		T const & GetTricubicInterpolated(float const X, float const Y, float const Z) const
		{
			int const iX = (int) X, iY = (int) Y, iZ = (int) Z;
			float const dX = X - floor(X), dY = Y - floor(Y), dZ = Z - floor(Z);
			T Values[4][4][4];

			for (int i = 0; i < 4; ++ i)
				for (int j = 0; j < 4; ++ j)
					for (int k = 0; k < 4; ++ k)
					{
						Values[i][j][k] = Get(iX - 1 + i, iY - 1 + j, iZ - 1 + k);
					}

			return TricubicInterpolate(Values, dX, dY, dZ);
		}

		template <typename U>
		T const & GetTricubicInterpolatedMember(float const X, float const Y, float const Z, U T:: *Member) const
		{
			int const iX = (int) X, iY = (int) Y, iZ = (int) Z;
			float const dX = X - floor(X), dY = Y - floor(Y), dZ = Z - floor(Z);
			T Values[4][4][4];

			for (int i = 0; i < 4; ++ i)
				for (int j = 0; j < 4; ++ j)
					for (int k = 0; k < 4; ++ k)
					{
						Values[i][j][k] = Get(iX - 1 + i, iY - 1 + j, iZ - 1 + k).*Member;
					}

			return TricubicInterpolate(Values, dX, dY, dZ);
		}

		class SRowAccess
		{
			SVolume<T> & Volume;
			int const X, Y;

			friend struct SVolume<T>;

			SRowAccess(SVolume<T> & volume, int const xIndex, int const yIndex)
				: Volume(volume), X(xIndex), Y(yIndex)
			{}

		public:

			T & operator[] (int const Z)
			{
				return Volume.Get(X, Y, Z);
			}

		};

		class SConstRowAccess
		{
			SVolume<T> const & Volume;
			int const X, Y;

			friend struct SVolume<T>;

			SConstRowAccess(SVolume<T> const & volume, int const xIndex, int const yIndex)
				: Volume(volume), X(xIndex), Y(yIndex)
			{}

		public:

			T const & operator[] (int const Z) const
			{
				return Volume.Get(X, Y, Z);
			}

		};

		class SLayerAccess
		{
			SVolume<T> & Volume;
			int const X;

			friend struct SVolume<T>;

			SLayerAccess(SVolume<T> & volume, int const index)
				: Volume(volume), X(index)
			{}

		public:

			SRowAccess operator[] (int const Y)
			{
				return SRowAccess(Volume, X, Y);
			}

		};

		class SConstLayerAccess
		{
			SVolume<T> const & Volume;
			int const X;

			friend struct SVolume<T>;

			SConstLayerAccess(SVolume<T> const & volume, int const index)
				: Volume(volume), X(index)
			{}

		public:

			SConstRowAccess operator[] (int const Y) const
			{
				return SConstRowAccess(Volume, X, Y);
			}

		};

		virtual SLayerAccess operator[] (int const X)
		{
			return SLayerAccess(* this, X);
		}

		virtual SConstLayerAccess operator[] (int const X) const
		{
			return SConstLayerAccess(* this, X);
		}

		virtual T & operator[] (vec3i const & index)
		{
			return Get(index.X, index.Y, index.Z);
		}

		virtual T & operator[] (glm::ivec3 const & index)
		{
			return Get(index.x, index.y, index.z);
		}

		virtual T const & operator[] (vec3i const & index) const
		{
			return Get(index.X, index.Y, index.Z);
		}

		virtual T const & operator[] (glm::ivec3 const & index) const
		{
			return Get(index.x, index.y, index.z);
		}

		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;

		virtual iterator begin()
		{
			return Values.begin();
		}

		virtual iterator end()
		{
			return Values.end();
		}

		virtual const_iterator begin() const
		{
			return Values.begin();
		}

		virtual const_iterator end() const
		{
			return Values.end();
		}
	};

}
