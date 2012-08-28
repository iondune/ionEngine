#ifndef _IONCORE_MATH_H_INCLUDED_
#define _IONCORE_MATH_H_INCLUDED_

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
static T const sq(T const a)
{
	return a * a;
}

#endif
