
/*!
\file ionClass.h
\brief Methods and classes for performing comparisons between numbers.
*/

#pragma once

#include "ionConfig.h"
#include "ionTypes.h"


////////////////////
// Rounding Error //
////////////////////

//! \brief Global constant for 32bit floating-point epsilon
f32 const RoundingError32 = 0.00001f;

//! \brief Global constant for 64bit floating-point epsilon
f64 const RoundingError64 = 0.00000001;

//! \brief Helper template to enable template-dependant epsilon values
//! \tparam T Type of number to retrieve epsilon value
template <typename T>
struct RoundingError
{
	ION_FUNC_DEF static T const Value()
	{
		return 0;
	}
};

//! \brief Template specialization of RoundingError for 32bit floating-point values
template <>
struct RoundingError<f32>
{
	ION_FUNC_DEF static f32 Value()
	{
		return RoundingError32;
	}
};

//! \brief Template specialization of RoundingError for 64bit floating-point values
template <>
struct RoundingError<f64>
{
	ION_FUNC_DEF static f64 Value()
	{
		return RoundingError64;
	}
};


//////////////
// Equality //
//////////////

//! \brief Template function for comparing two values for equality within an epsilon range
template <typename T>
ION_FUNC_DEF static inline bool Equals(T const a, T const b, T const epsilon = RoundingError<T>::Value())
{
	return (a + epsilon >= b) && (a - epsilon <= b);
}


////////////////
// Comparison //
////////////////

//! \brief Template function for selecting the minimum of two values
template <typename T>
ION_FUNC_DEF static inline T Minimum(T const & a, T const & b)
{
	return a < b ? a : b;
}

//! \brief Template function for selecting the maximum of two values
template <typename T>
ION_FUNC_DEF static inline T Maximum(T const & a, T const & b)
{
	return b < a ? a : b;
}

//! \brief Template function for selecting the minimum of three values
template <typename T>
ION_FUNC_DEF static T const Minimum(T const & a, T const & b, T const & c)
{
	return Minimum(a, Minimum(b, c));
}

//! \brief Template function for selecting the maximum of three values
template <typename T>
ION_FUNC_DEF static T const Maximum(T const & a, T const & b, T const & c)
{
	return Maximum(a, Maximum(b, c));
}

//! \brief Template function for selecting the minimum of four values
template <typename T>
ION_FUNC_DEF static T const Minimum(T const & a, T const & b, T const & c, T const & d)
{
	return Minimum(a, Minimum(b, c, d));
}

//! \brief Template function for selecting the maximum of four values
template <typename T>
ION_FUNC_DEF static T const Maximum(T const & a, T const & b, T const & c, T const & d)
{
	return Maximum(a, Maximum(b, c, d));
}


//! \brief Template function for selecting the minimum of two values
template <typename T>
ION_FUNC_DEF static T const Min(T const & a, T const & b)
{
	return a < b ? a : b;
}

//! \brief Template function for selecting the maximum of two values
template <typename T>
ION_FUNC_DEF static T const Max(T const & a, T const & b)
{
	return b < a ? a : b;
}

//! \brief Template function for selecting the minimum of three values
template <typename T>
ION_FUNC_DEF static T const Min(T const & a, T const & b, T const & c)
{
	return Min(a, Min(b, c));
}

//! \brief Template function for selecting the maximum of three values
template <typename T>
ION_FUNC_DEF static T const Max(T const & a, T const & b, T const & c)
{
	return Max(a, Max(b, c));
}

//! \brief Template function for selecting the minimum of four values
template <typename T>
ION_FUNC_DEF static T const Min(T const & a, T const & b, T const & c, T const & d)
{
	return Min(a, Min(b, c, d));
}

//! \brief Template function for selecting the maximum of four values
template <typename T>
ION_FUNC_DEF static T const Max(T const & a, T const & b, T const & c, T const & d)
{
	return Max(a, Max(b, c, d));
}

//! \brief Template function for selecting from two values the one with larger magnitude
//! The aboslute values of a and b are compared, but the original values of a or b
//! are returned.
template <typename T>
ION_FUNC_DEF static T const MaxAbs(T const & a, T const & b)
{
	return Abs(b) < Abs(a) ? a : b;
}
