#ifndef _IONCORE_UTILS_H_INCLUDED_
#define _IONCORE_UTILS_H_INCLUDED_

#include "ionMath.h"
#include "ionComparison.h"

#include <iostream>


//! Portable version of system("PAUSE")
static void waitForUser() 
{
	std::cout << "Press [Enter] to continue . . .";
	std::cin.get();
}

#endif
