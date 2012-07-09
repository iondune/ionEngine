#ifndef _CABBAGE_CORE_SVECTOR2_H_INCLUDED_
#define _CABBAGE_CORE_SVECTOR2_H_INCLUDED_

#include <cmath>
#include <stdio.h>

#include "ionUtils.h"
#include "SPosition2.h"

template <typename T>
class SVector2;

template <typename T>
class SVector2Reference
{
	
	SVector2Reference();
	SVector2Reference & operator = (SVector2Reference const &);

public:

	T & X, & Y;

	SVector2Reference(T & x, T & y)
		: X(x), Y(y)
	{}

	SVector2Reference(SVector2Reference const & v)
		: X(v.X), Y(v.Y)
	{}

	float const operator[] (int i) const
	{
		return (i == 0 ? X : Y);
	}

	T & operator[] (int i)
	{
		return (i == 0 ? X : Y);
	}

	void reset()
	{
		X = 0;
		Y = 0;
	}

	void set(T in)
	{
		X = in;
		Y = in;
	}

	void set(T in_x, T in_y)
	{
		X = in_x;
		Y = in_y;
	}

	T dotProduct(SVector2Reference<T> const & v) const
	{
		return X*v.X + Y*v.Y;
	}

	T const length() const
	{
		return sqrtf(X*X + Y*Y);
	}

	T getDistanceFrom(SVector2Reference<T> const & v) const;

	SVector2<T> getInterpolated(SVector2Reference<T> const & v, T const d);

	SVector2<T> operator + (SVector2Reference<T> const & v) const;

	SVector2<T> operator - (SVector2Reference<T> const & v) const;

	SVector2<T> operator * (SVector2Reference<T> const & v) const;

	SVector2<T> operator / (SVector2Reference<T> const & v) const;

	SVector2<T> operator + (SVector2<T> const & v) const;

	SVector2<T> operator - (SVector2<T> const & v) const;

	SVector2<T> operator * (SVector2<T> const & v) const;

	SVector2<T> operator / (SVector2<T> const & v) const;

	SVector2<T> operator * (T const s) const;

	SVector2<T> operator / (T const s) const;

	SVector2Reference & operator += (SVector2Reference const & v)
	{
		X += v.X;
		Y += v.Y;

		return * this;
	}

	SVector2Reference & operator -= (SVector2Reference const & v)
	{
		X -= v.X;
		Y -= v.Y;

		return * this;
	}

	SVector2Reference & operator *= (SVector2Reference const & v)
	{
		X *= v.X;
		Y *= v.Y;

		return * this;
	}

	SVector2Reference & operator /= (SVector2Reference const & v)
	{
		X /= v.X;
		Y /= v.Y;

		return * this;
	}

	SVector2Reference & operator *= (T const s)
	{
		X *= s;
		Y *= s;

		return * this;
	}

	SVector2Reference & operator /= (T const s)
	{
		X /= s;
		Y /= s;

		return * this;
	}

	bool const operator <= (SVector2Reference const & v) const
	{
		return (X < v.X && Y < v.Y);
	}

	bool const operator >= (SVector2Reference const & v) const
	{
		return (X > v.X && Y > v.Y);
	}

	bool const operator == (SVector2Reference const & v) const
	{
		return equals(v);
	}

	bool const operator != (SVector2Reference const & v) const
	{
		return ! equals(v);
	}

	bool const equals(SVector2Reference const & v, float const Epsilon = RoundingError32) const
	{
		return ::equals(X, v.X, Epsilon) && ::equals(Y, v.Y, Epsilon);
	}

};

template <typename T>
class SVector2 : public SVector2Reference<T>
{

public:

	T X, Y;

	SVector2()
		: X(0), Y(0), SVector2Reference<T>(X, Y)
	{}

	template <typename U>
	SVector2(SVector2<U> const & vec)
		: X((T) vec.X), Y((T) vec.Y), SVector2Reference<T>(X, Y)
	{}

	SVector2(SPosition2 const & vec)
		: X((T) vec.X), Y((T) vec.Y), SVector2Reference<T>(X, Y)
	{}
	
	template <typename U>
	SVector2(SVector2Reference<U> const & vec)
		: X(vec.X), Y(vec.Y), SVector2Reference<T>(X, Y)
	{}
	
	SVector2(SVector2<T> const & vec)
		: X(vec.X), Y(vec.Y), SVector2Reference<T>(X, Y)
	{}

	SVector2(T in)
		: X(in), Y(in), SVector2Reference<T>(X, Y)
	{}

	SVector2(T in_x, T in_y)
		: X(in_x), Y(in_y), SVector2Reference<T>(X, Y)
	{}

	SVector2<T> & operator = (SVector2Reference<T> const & vec)
	{
		X = vec.X;
		Y = vec.Y;

		return * this;
	}

	SVector2<T> & operator = (SVector2<T> const & vec)
	{
		X = vec.X;
		Y = vec.Y;

		return * this;
	}

};

template <typename T>
T SVector2Reference<T>::getDistanceFrom(SVector2Reference<T> const & v) const
{
	return (v - * this).length();
}

template <typename T>
SVector2<T> SVector2Reference<T>::getInterpolated(SVector2Reference<T> const & v, T const d)
{
	T inv = (T) 1.0 - d;
	return SVector2<T>((v.X*inv + X*d), (v.Y*inv + Y*d));
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator + (SVector2Reference<T> const & v) const
{
	return SVector2<T>(X+v.X, Y+v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator - (SVector2Reference<T> const & v) const
{
	return SVector2<T>(X-v.X, Y-v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator * (SVector2Reference<T> const & v) const
{
	return SVector2<T>(X*v.X, Y*v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator / (SVector2Reference<T> const & v) const
{
	return SVector2<T>(X/v.X, Y/v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator + (SVector2<T> const & v) const
{
	return SVector2<T>(X+v.X, Y+v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator - (SVector2<T> const & v) const
{
	return SVector2<T>(X-v.X, Y-v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator * (SVector2<T> const & v) const
{
	return SVector2<T>(X*v.X, Y*v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator / (SVector2<T> const & v) const
{
	return SVector2<T>(X/v.X, Y/v.Y);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator * (T const s) const
{
	return SVector2<T>(X*s, Y*s);
}

template <typename T>
SVector2<T> SVector2Reference<T>::operator / (T const s) const
{
	return SVector2<T>(X/s, Y/s);
}

typedef SVector2<float> SVector2f;
typedef SVector2<double> SVector2d;

#endif
