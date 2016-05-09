
#pragma once

#include "SVector.h"
#include "Utilities.h"


template <typename T>
class SVector2 : public SVector<T, 2, SVector2<T> >
{

public:

	using SVectorBase<T, 2>::Values;
	using SVectorBase<T, 2>::reset;
	using SVectorBase<T, 2>::set;

	T & X, & Y;

	//! Default constructor
	SVector2()
		: X(Values[0]), Y(Values[1])
	{
		reset();
	}

	//! Scalar constructor
	SVector2(T const in)
		: X(Values[0]), Y(Values[1])
	{
		set(in);
	}

	//! Explicit constructor
	SVector2(T const x, T const y)
		: X(Values[0]), Y(Values[1])
	{
		Values[0] = x;
		Values[1] = y;
	}

	//! Copy constructor
	SVector2(SVector2<T> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}

	//! Generic vector constructor
	template <typename U>
	SVector2(SVectorBase<U, 2> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}

	//! Assignment operator
	SVector2<T> & operator = (SVector2<T> const & vec)
	{
		set(vec);

		return * this;
	}

	//! Generic vector assignment operator
	template <typename U, u32 otherDimension, typename otherImplementation>
	SVector2<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(vec);

		return * this;
	}

	SVector2<T> Rotate(T const radians) const
	{
		SVector2<T> Ret;
		T C = Cos(radians);
		T S = Sin(radians);
		Ret.X = X * C - Y * S;
		Ret.Y = X * S + Y * C;
		return Ret;
	}

	T GetAngle() const
	{
		return ArcTan(Y, X);
	}

	friend std::ostream & operator << (std::ostream & stream, SVector2<T> const & vec)
	{
		return stream << vec.X << " " << vec.Y;
	}

	SVector2<T> YX() const
	{
		return SVector2<T>(Y, X);
	}

};

template <typename T>
using vec2 = SVector2<T>;

typedef SVector2<f32> SVector2f;
typedef SVector2<f64> SVector2d;
typedef SVector2<s32> SVector2i;
typedef SVector2<u32> SVector2u;

typedef SVector2f vec2f;
typedef SVector2d vec2d;
typedef SVector2i vec2i;
typedef SVector2u vec2u;
