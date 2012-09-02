#ifndef _IONCORE_UTILS_H_INCLUDED_
#define _IONCORE_UTILS_H_INCLUDED_

#include "ionPrimitives.h"
#include "ionMath.h"
#include "ionComparison.h"

#include <iostream>


//! Portable version of system("PAUSE")
static void waitForUser() 
{
	std::cout << "Press [Enter] to continue . . .";
	std::cin.get();
}

static u32 const digitCount(s32 n)
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

#endif
