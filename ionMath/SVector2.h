#pragma once

#include "SVector.h"


template <typename T>
class SVector2 : public SVector<T, 2, SVector2<T> >
{

public:

	T & X, & Y;

	//! Default constructor
	ION_FUNC_DEF SVector2()
		: X(Values[0]), Y(Values[1])
	{
		reset();
	}
	
	//! Scalar constructor
	ION_FUNC_DEF SVector2(T const in)
		: X(Values[0]), Y(Values[1])
	{
		set(in);
	}

	//! Explicit constructor
	ION_FUNC_DEF SVector2(T const x, T const y)
		: X(Values[0]), Y(Values[1])	
	{
		Values[0] = x;
		Values[1] = y;
	}

	//! Copy constructor
	ION_FUNC_DEF SVector2(SVector2<T> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}
	
	//! Generic vector constructor
	template <typename U, u32 otherDimension, typename otherImplementation>
	ION_FUNC_DEF SVector2(SVector<U, otherDimension, otherImplementation> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}

	//! Assignment operator
	ION_FUNC_DEF SVector2<T> & operator = (SVector2<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	//! Generic vector assignment operator
	template <typename U, u32 otherDimension, typename otherImplementation>
	ION_FUNC_DEF SVector2<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(vec);

		return * this;
	}

};


typedef SVector2<f32> SVector2f;
typedef SVector2<f64> SVector2d;
typedef SVector2<s32> SVector2i;
typedef SVector2<u32> SVector2u;

typedef SVector2f vec2f;
typedef SVector2d vec2d;
typedef SVector2i vec2i;
typedef SVector2u vec2u;
