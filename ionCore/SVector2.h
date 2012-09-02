#ifndef _CABBAGE_CORE_SVECTOR2_H_INCLUDED_
#define _CABBAGE_CORE_SVECTOR2_H_INCLUDED_

#include "SVector.h"


template <typename T>
class SVector2 : public SVector<T, 2, SVector2<T> >
{

public:

	T & X, & Y;

	SVector2()
		: X(Values[0]), Y(Values[1])
	{
		SVectorSimple<T, Dimension>::set((T) 0);
	}

	SVector2(T const in)
		: X(Values[0]), Y(Values[1])
	{
		SVectorSimple<T, Dimension>::set(in);
	}

	SVector2(T const x, T const y)
		: X(Values[0]), Y(Values[1])	
	{
		Values[0] = x;
		Values[1] = y;
	}

	SVector2(T const & x, T const & y, ForceReference)
		: X(x), Y(y)
	{}

	SVector2(SVector2<T> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SVector2(SVector<U, otherDimension, otherImplementation> const & vec)
		: X(Values[0]), Y(Values[1])
	{
		set(vec);
	}

	SVector2<T> & operator = (SVector2<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SVector2<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(v);

		return * this;
	}

};

typedef SVector2<float> SVector2f;
typedef SVector2<double> SVector2d;
typedef SVector2<int> SVector2i;
typedef SVector2<unsigned int> SVector2u;

// Legacy
typedef SVector2i SPosition2;
typedef SVector2i SSize2;

#endif
