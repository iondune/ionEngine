#ifndef _IONCORE_UTILS_H_INCLUDED_
#define _IONCORE_UTILS_H_INCLUDED_

#include "ionConfig.h"
#include "ionTypes.h"

#include "ionComparison.h"

#include <iostream>


//! Portable version of system("PAUSE")
static void waitForUser() 
{
	std::cout << "Press [Enter] to continue . . .";
	std::cin.get();
}

//! Count the number of digits (included a - for negative numbers) in an integer
static u32 digitCount(s32 n)
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
