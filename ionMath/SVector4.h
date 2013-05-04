#ifndef _ION_CORE_SVECTOR4_H_INCLUDED_
#define _ION_CORE_SVECTOR4_H_INCLUDED_

#include <ionConfig.h>

#include "SVector.h"
#include "SVector3.h"


template <typename T>
class SVector4 : public SVector<T, 4, SVector4<T> >
{

public:

	T & X, & Y, & Z, & W;

	//! Default constructor
	ION_FUNC_DEF SVector4()
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		SVectorBase<T, 4>::set((T) 0);
	}
	
	//! Scalar constructor
	ION_FUNC_DEF SVector4(T const in)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		SVectorBase<T, 4>::set(in);
	}

	//! Explicit constructor
	ION_FUNC_DEF SVector4(T const x, T const y, T const z, T const w)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		Values[0] = x;
		Values[1] = y;
		Values[2] = z;
		Values[3] = w;
	}

	//! Reference constructor
	ION_FUNC_DEF SVector4(T const & x, T const & y, T const & z, T const & w, ForceReference)
		: X(x), Y(y), Z(z), W(w)
	{}

	//! Copy constructor
	ION_FUNC_DEF SVector4(SVector4<T> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		SVectorBase<T, 4>::set(vec);
	}
	
	//! Generic vector constructor
	template <typename U, int otherDimension, typename otherImplementation>
	ION_FUNC_DEF SVector4(SVector<U, otherDimension, otherImplementation> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		SVectorBase<T, 4>::set(vec);
	}
	
	//! Generic vector constructor
	ION_FUNC_DEF SVector4(SVectorBase<T, 3> const & vec, T const W = 1)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		Values[0] = vec[0];
		Values[1] = vec[1];
		Values[2] = vec[2];
		Values[3] = W;
	}

	//! Assignment operator
	ION_FUNC_DEF SVector4<T> & operator = (SVector4<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	//! Generic vector assignment operator
	template <typename U, int otherDimension, typename otherImplementation>
	ION_FUNC_DEF SVector4<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(vec);

		return * this;
	}

	ION_FUNC_DEF SVector3<T> xyz() const
	{
		return SVector3<T>(Values[0], Values[1], Values[2]);
	}

};

typedef SVector4<f32> SVector4f;
typedef SVector4<f64> SVector4d;
typedef SVector4<s32> SVector4i;
typedef SVector4<u32> SVector4u;

typedef SVector4f vec4f;
typedef SVector4d vec4d;
typedef SVector4i vec4i;
typedef SVector4u vec4u;

#endif
