
#pragma once

#include "ionConstants.h"
#include <cmath>


namespace ion
{

	//! \ingroup ionCore
	template <typename T>
	T Abs(T const value)
	{
		return std::abs(value);
	}

	//! \brief Template function for selecting from two values the one with larger magnitude
	//! \ingroup ionCore
	//! The absolute values of a and b are compared, but the original values of a or b
	//! are returned.
	template <typename T>
	static T const MaxAbs(T const a, T const b)
	{
		return Abs(b) < Abs(a) ? a : b;
	}


	//! \ingroup ionCore
	template <typename T>
	T Sin(T const value)
	{
		return sin(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T ArcSin(T const value)
	{
		return asin(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T Cos(T const value)
	{
		return cos(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T ArcCos(T const value)
	{
		return acos(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T Tan(T const value)
	{
		return tan(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T ArcTan(T const value)
	{
		return atan(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T ArcTan(T const y, T const x)
	{
		return atan2(y, x);
	}

	//! \ingroup ionCore
	template <typename T>
	T Sqrt(T const value)
	{
		return (T) sqrt(value);
	}

	//! \ingroup ionCore
	template <typename T>
	T DegToRad(T const degrees)
	{
		return degrees * Constants<T>::Pi() / 180;
	}

	//! \ingroup ionCore
	template <typename T>
	T RadToDeg(T const radians)
	{
		return radians * 180 / Constants<T>::Pi();
	}

	//! \ingroup ionCore
	template <typename T>
	bool IsNaN(T const value)
	{
		return value != value;
	}

	//! \brief Clamps a value between 0 and 1
	//! \ingroup ionCore
	//! \return value clamped between 0 and 1
	template <typename T>
	T Saturate(T const value)
	{
		return Minimum(1, Maximum(0, value));
	}

}
