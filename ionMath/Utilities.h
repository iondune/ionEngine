
#pragma once

#include <ionCore.h>
#include <cmath>

#include "Constants.h"


template <typename T>
T Abs(T const & value)
{
	return abs(value);
}

template <typename T>
T AbsoluteValue(T const & value)
{
	return abs(value);
}

//! \brief Template function for selecting from two values the one with larger magnitude
//! The aboslute values of a and b are compared, but the original values of a or b
//! are returned.
template <typename T>
ION_FUNC_DEF static T const MaxAbs(T const & a, T const & b)
{
	return Abs(b) < Abs(a) ? a : b;
}


template <typename T>
T Sin(T const & value)
{
	return sin(value);
}

template <typename T>
T Cos(T const & value)
{
	return cos(value);
}

template <typename T>
T Tan(T const & value)
{
	return tan(value);
}

template <typename T>
T ArcTan(T const & value)
{
	return atan(value);
}

template <typename T>
T ArcTan(T const & y, T const & x)
{
	return atan2(y, x);
}


template <typename T>
T Sqrt(T const & value)
{
	return sqrt(value);
}


template <typename T>
T DegToRad(T const & degrees)
{
	return degrees * Constants<T>::Pi() / 180;
}

template <typename T>
T DegreesToRadians(T const & degrees)
{
	return degrees * Constants<T>::Pi() / 180;
}

template <typename T>
T RadToDeg(T const & radians)
{
	return radians * 180 / Constants<T>::Pi();
}

template <typename T>
T RadiansToDegrees(T const & radians)
{
	return radians * 180 / Constants<T>::Pi();
}


template <typename T>
bool IsNaN(T const & value)
{
	return value != value;
}
