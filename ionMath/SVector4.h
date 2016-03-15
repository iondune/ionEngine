
#pragma once

#include <ionConfig.h>

#include "SVector.h"
#include "SVector3.h"


template <typename T>
class SVector4 : public SVector<T, 4, SVector4<T> >
{

public:

	using SVectorBase<T, 4>::Values;
	using SVectorBase<T, 4>::set;

	T & X, & Y, & Z, & W;

	//! Default constructor
	SVector4()
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		set((T) 0);
	}

	//! Scalar constructor
	SVector4(T const in)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		set(in);
	}

	//! Explicit constructor
	SVector4(T const x, T const y, T const z, T const w)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		Values[0] = x;
		Values[1] = y;
		Values[2] = z;
		Values[3] = w;
	}

	//! GLM constructor
	template <typename U>
	SVector4(glm::tvec4<U, glm::defaultp> const & v)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		Values[0] = (T) v.x;
		Values[1] = (T) v.y;
		Values[2] = (T) v.z;
		Values[3] = (T) v.w;
	}

	//! Copy constructor
	SVector4(SVector4<T> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		set(vec);
	}

	//! Generic vector constructor
	template <typename U, u32 OtherDimension>
	SVector4(SVectorBase<U, OtherDimension> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		set(vec);
	}

	//! Generic vector constructor
	SVector4(SVectorBase<T, 3> const & vec, T const W = 1)
		: X(Values[0]), Y(Values[1]), Z(Values[2]), W(Values[3])
	{
		Values[0] = vec[0];
		Values[1] = vec[1];
		Values[2] = vec[2];
		Values[3] = W;
	}

	//! Assignment operator
	SVector4<T> & operator = (SVector4<T> const & vec)
	{
		set(vec);

		return * this;
	}

	//! Generic vector assignment operator
	template <typename U, u32 OtherDimension>
	SVector4<T> & operator = (SVectorBase<U, OtherDimension> const & vec)
	{
		set(vec);

		return * this;
	}

	SVector2<T> XY() const
	{
		return SVector2<T>(X, Y);
	}

	SVector2<T> XZ() const
	{
		return SVector2<T>(X, Z);
	}

	SVector2<T> XW() const
	{
		return SVector2<T>(X, W);
	}

	SVector2<T> YZ() const
	{
		return SVector2<T>(Y, Z);
	}

	SVector2<T> ZW() const
	{
		return SVector2<T>(Z, W);
	}

	SVector3<T> XYZ() const
	{
		return SVector3<T>(Values[0], Values[1], Values[2]);
	}

	//! GLM constructor
	template <typename U>
	operator glm::tvec4<U, glm::defaultp> ()
	{
		return glm::tvec4<U, glm::defaultp>(X, Y, Z, W);
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

