#pragma once

#include "ionConfig.h"
#include "ionTypes.h"
#include "ionComparison.h"

#include <iostream>


//! Portable version of system("PAUSE")
ION_FUNC_DEF static void WaitForUser() 
{
	std::cout << "Press [Enter] to continue . . .";
	std::cin.get();
}

//! Count the number of digits (including a - for negative numbers) in a decimal integer
ION_FUNC_DEF static u32 DigitCount(s32 n)
{
	u32 count = 1;
	if (n < 0)
	{
		n *= -1;
		++ count;
	}

	while (n > 10)
	{
		++ count;
		n /= 10;
	}

	return count;
}

template <typename T>
ION_FUNC_DEF static T const Clamp(T const v, T const min, T const max)
{
	return ((v > max) ? max : ((v < min) ? min : v));
}

template <typename T>
ION_FUNC_DEF static T const Sq(T const a)
{
	return a * a;
}

template <typename T> s32 Sign(T val)
{
	return (T(0) < val) - (val < T(0));
}
