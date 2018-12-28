
#pragma once

#include <ionCore.h>


namespace ion
{

	template <typename T>
	struct SGrid
	{
		vector<T> Values;
		vec2i Dimensions;

		SGrid(vec2i const & dimensions = vec2i())
			: Dimensions(dimensions), Values()
		{
			Allocate();
		}

		SGrid(T const & init, vec2i const & dimensions = vec2i())
			: Dimensions(dimensions), Values()
		{
			Allocate(init);
		}

		virtual void Allocate()
		{
			Values.resize(Dimensions.X * Dimensions.Y);
		}

		virtual void Allocate(T const & value)
		{
			Values.resize(Dimensions.X * Dimensions.Y, value);
		}

		virtual bool const InBounds(vec2i const Index) const
		{
			return InBounds(Index.X, Index.Y);
		}

		virtual bool const InBounds(int const X, int const Y) const
		{
			return X >= 0 && X < Dimensions.X &&
				Y >= 0 && Y < Dimensions.Y;
		}

		virtual T & Get(vec2i const Index)
		{
			return Get(Index.X, Index.Y);
		}

		virtual T const & Get(vec2i const Index) const
		{
			return Get(Index.X, Index.Y);
		}

		virtual T & Get(int const X, int const Y)
		{
			int const Index = Clamp(X, 0, Dimensions.X - 1) + Dimensions.X * Clamp(Y, 0, Dimensions.Y - 1);
			return Values[Index];
		}

		virtual T const & Get(int const X, int const Y) const
		{
			int const Index = Clamp(X, 0, Dimensions.X - 1) + Dimensions.X * Clamp(Y, 0, Dimensions.Y - 1);
			return Values[Index];
		}

		class SRowAccess
		{
			SGrid<T> & Volume;
			int const X;

			friend struct SGrid<T>;

			SRowAccess(SGrid<T> & volume, int const xIndex)
				: Volume(volume), X(xIndex)
			{}

		public:

			T & operator[] (int const Y)
			{
				return Volume.Get(X, Y);
			}

		};

		class SConstRowAccess
		{
			SGrid<T> const & Volume;
			int const X;

			friend struct SGrid<T>;

			SConstRowAccess(SGrid<T> const & volume, int const xIndex)
				: Volume(volume), X(xIndex)
			{}

		public:

			T const & operator[] (int const Y) const
			{
				return Volume.Get(X, Y);
			}

		};

		virtual SRowAccess operator[] (int const X)
		{
			return SRowAccess(* this, X);
		}

		virtual SConstRowAccess operator[] (int const X) const
		{
			return SConstRowAccess(* this, X);
		}

		virtual T & operator[] (vec2i const & index)
		{
			return Get(index.X, index.Y);
		}

		virtual T const & operator[] (vec2i const & index) const
		{
			return Get(index.X, index.Y);
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
