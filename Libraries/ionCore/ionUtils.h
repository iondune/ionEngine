
/*!
\file ionUtils.h
\ingroup ionCore
\brief General helper functions
*/


#pragma once

#include "ionTypes.h"


//! \brief Standard macro for computing size of a C-style array
//! \ingroup ionCore
//! More discussion here: https://stackoverflow.com/a/4415646/1390945
#define ION_ARRAYSIZE(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


namespace ion
{

	//! \brief Portable version of system("PAUSE")
	//! \ingroup ionCore
	void WaitForUser();

	//! \brief Count the number of digits (including a - for negative numbers) in a decimal integer
	//! \ingroup ionCore
	int DigitCount(int n);

	//! \ingroup ionCore
	int MakeEven(int const i);

	//! \ingroup ionCore
	int RoundUp(int const x, int const multiple);

	//! \ingroup ionCore
	bool ToggleBool(bool & Condition);

	char const * BoolToString(bool const B);

	//! \ingroup ionCore
	float Saturate(float const v);

	//! \ingroup ionCore
	double Saturate(double const v);

	//! \ingroup ionCore
	template <typename T>
	T Clamp(T const v, T const min, T const max)
	{
		return ((v > max) ? max : ((v < min) ? min : v));
	}

	//! \ingroup ionCore
	template <typename T>
	T Sq(T const a)
	{
		return a * a;
	}

	//! \ingroup ionCore
	template <typename T>
	T Average(T const a, T const b)
	{
		return (a + b) / 2;
	}

	//! \ingroup ionCore
	template <typename T>
	T Average(T const a, T const b, T const c)
	{
		return (a + b + c) / 3;
	}

	//! \ingroup ionCore
	template <typename T>
	T Average(T const a, T const b, T const c, T const d)
	{
		return (a + b + c + d) / 4;
	}

	//! \ingroup ionCore
	template <typename T>
	T Sign(T const val)
	{
		return (T) ((0 < val) - (val < 0));
	}

}
