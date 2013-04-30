#ifndef _ION_CORE_COMPARISON_H_INCLUDED_
#define _ION_CORE_COMPARISON_H_INCLUDED_

#include "ionConfig.h"

#include <cstdlib>
#include <algorithm>


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
struct RoundingError<float>
{
	ION_FUNC_DEF static float  Value()
	{
		return RoundingError32;
	}
};

template <>
struct RoundingError<double>
{
	ION_FUNC_DEF static double Value()
	{
		return RoundingError64;
	}
};


//////////////
// Equality //
//////////////

template <typename T>
ION_FUNC_DEF static bool equals(T const a, T const b, T const epsilon = RoundingError<T>::Value())
{
	return (a + epsilon >= b) && (a - epsilon <= b);
}


////////////////
// Comparison //
////////////////

template <typename T>
ION_FUNC_DEF static T const min(T const a, T const b)
{
	return std::min(a, b);
}

template <typename T>
ION_FUNC_DEF static T const max(T const a, T const b)
{
	return std::max(a, b);
}

template <typename T>
ION_FUNC_DEF static T const min(T const a, T const b, T const c)
{
	return min(a, min(b, c));
}

template <typename T>
ION_FUNC_DEF static T const max(T const a, T const b, T const c)
{
	return max(a, max(b, c));
}

template <typename T>
ION_FUNC_DEF static T const min(T const a, T const b, T const c, T const d)
{
	return min(a, min(b, c, d));
}

template <typename T>
ION_FUNC_DEF static T const max(T const a, T const b, T const c, T const d)
{
	return max(a, max(b, c, d));
}

#endif
