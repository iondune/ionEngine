#ifndef _CABBAGE_CORE_UTILS_H_INCLUDED_
#define _CABBAGE_CORE_UTILS_H_INCLUDED_

#include <cmath>
#include <iostream>

const float RoundingError32 = 0.00001f;
const double RoundingError64 = 0.00000001;

template <typename T>
struct RoundingError
{
	static T const Value()
	{
		return 0;
	}
};

template <>
struct RoundingError<float>
{
	static float const Value()
	{
		return RoundingError32;
	}
};

template <>
struct RoundingError<double>
{
	static double const Value()
	{
		return RoundingError64;
	}
};

template <typename T>
static bool const equals(T const a, T const b, T const epsilon = RoundingError<T>::Value())
{
	return (a + epsilon >= b) && (a - epsilon <= b);
}

//! Portable version of system("PAUSE")
static void waitForUser() 
{
	std::cout << "Press [Enter] to continue . . .";
	std::cin.get();
}

#include <cstdlib>

static float frand()
{
	return std::rand() / (float) RAND_MAX;
}

template <typename T>
static T const clamp(T const v, T const min, T const max)
{
	return ((v > max) ? max : ((v < min) ? min : v));
}

template <typename T>
static T const min(T const a, T const b, T const c)
{
	return std::min(a, std::min(b, c));
}

template <typename T>
static T const max(T const a, T const b, T const c)
{
	return std::max(a, std::max(b, c));
}

template <typename T>
static T const min(T const a, T const b, T const c, T const d)
{
	return std::min(a, min(b, c, d));
}

template <typename T>
static T const max(T const a, T const b, T const c, T const d)
{
	return std::max(a, max(b, c, d));
}

template <typename T>
static T const sq(T const a)
{
	return a * a;
}

#endif
