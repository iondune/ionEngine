
#include "ionUtils.h"

#include <iostream>


namespace ion
{

	void WaitForUser()
	{
		std::cout << "Press [Enter] to continue . . .";
		std::cin.get();
	}

	int DigitCount(int n)
	{
		int count = 1;

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

	int MakeEven(int const i)
	{
		return (i % 2) ? (i - 1) : (i);
	}

	int Sign(int const val)
	{
		return (0 < val) - (val < 0);
	}

	bool ToggleBool(bool & Condition)
	{
		return Condition = ! Condition;
	}

	float Saturate(float const v)
	{
		return ((v > 1.f) ? 1.f : ((v < 0.f) ? 0.f : v));
	}

	double Saturate(double const v)
	{
		return ((v > 1.0) ? 1.0 : ((v < 0.0) ? 0.0 : v));
	}

}
