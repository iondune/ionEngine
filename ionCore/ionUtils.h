
/*!
\file ionUtils.h
\ingroup ionCore
\brief General helper functions
*/


#pragma once

#include "ionConfig.h"
#include "ionTypes.h"
#include "ionComparison.h"

#include <iostream>


//! \brief Portable version of system("PAUSE")
//! \ingroup ionCore
static void WaitForUser()
{
	std::cout << "Press [Enter] to continue . . .";
	std::cin.get();
}

//! \brief Standard macro for computing size of a C-style array
//! \ingroup ionCore
//! More discussion here: https://stackoverflow.com/a/4415646/1390945
#define ION_ARRAYSIZE(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

//! \brief Count the number of digits (including a - for negative numbers) in a decimal integer
//! \ingroup ionCore
static inline int DigitCount(int n)
{
	u32 count = 1;
	if (n < 0)
	{
		n *= -1;
		++ count;
	}

	while (n >= 10)
	{
		++ count;
		n /= 10;
	}

	return count;
}

//! \ingroup ionCore
template <typename T>
T Clamp(T const & v, T const & min, T const & max)
{
	return ((v > max) ? max : ((v < min) ? min : v));
}

//! \ingroup ionCore
template <typename T>
T Sq(T const & a)
{
	return a * a;
}

//! \ingroup ionCore
template <typename T>
T Average(T const & a, T const & b)
{
	return (a + b) / 2;
}

//! \ingroup ionCore
template <typename T>
T Average(T const & a, T const & b, T const & c)
{
	return (a + b + c) / 3;
}

//! \ingroup ionCore
template <typename T>
T Average(T const & a, T const & b, T const & c, T const & d)
{
	return (a + b + c + d) / 4;
}

//! \ingroup ionCore
template <typename T>
T MakeEven(T const i)
{
	return (i % 2) ? (i - 1) : (i);
}

//! \ingroup ionCore
template <typename T>
s32 Sign(T const & val)
{
	return (T(0) < val) - (val < T(0));
}

//! \ingroup ionCore
template <typename T>
T ToggleBool(T & Condition)
{
	return Condition = ! Condition;
}
