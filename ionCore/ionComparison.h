#pragma once

#include "ionConfig.h"


////////////////////
// Rounding Error //
////////////////////

f32 const RoundingError32 = 0.00001f;
f64 const RoundingError64 = 0.00000001;

template <typename T>
struct RoundingError
{
	ION_FUNC_DEF static T const Value()
	{
		return 0;
	}
};

template <>
struct RoundingError<f32>
{
	ION_FUNC_DEF static f32 Value()
	{
		return RoundingError32;
	}
};

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

template <typename T>
ION_FUNC_DEF static bool Equals(T const a, T const b, T const epsilon = RoundingError<T>::Value())
{
	return (a + epsilon >= b) && (a - epsilon <= b);
}


////////////////
// Comparison //
////////////////

template <typename T>
ION_FUNC_DEF static T const Minimum(T const & a, T const & b)
{
	return a < b ? a : b;
}

template <typename T>
ION_FUNC_DEF static T const Maximum(T const & a, T const & b)
{
	return b < a ? a : b;
}

template <typename T>
ION_FUNC_DEF static T const Minimum(T const & a, T const & b, T const & c)
{
	return Minimum(a, Minimum(b, c));
}

template <typename T>
ION_FUNC_DEF static T const Maximum(T const & a, T const & b, T const & c)
{
	return Maximum(a, Maximum(b, c));
}

template <typename T>
ION_FUNC_DEF static T const Minimum(T const & a, T const & b, T const & c, T const & d)
{
	return Minimum(a, Minimum(b, c, d));
}

template <typename T>
ION_FUNC_DEF static T const Maximum(T const & a, T const & b, T const & c, T const & d)
{
	return Maximum(a, Maximum(b, c, d));
}
