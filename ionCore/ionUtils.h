#ifndef _CABBAGE_CORE_UTILS_H_INCLUDED_
#define _CABBAGE_CORE_UTILS_H_INCLUDED_

#include <cmath>
#include <iostream>

const float RoundingError32 = 0.00001f;
const double RoundingError64 = 0.00000001;

static bool const equals(float const a, float const b, float const epsilon = RoundingError32)
{
	return (a + epsilon >= b) && (a - epsilon <= b);
}

static bool const equals(double const a, double const b, double const epsilon = RoundingError64)
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

#endif
