
#pragma once

#include <ionConfig.h>
#include "ionTypes.h"

#include <cstdlib>


namespace ion
{

	//! \brief Generates a random number in the range [0, 1) using std::rand
	//! \ingroup ionCore
	static inline float frand()
	{
		return std::rand() / (float) RAND_MAX;
	}

	//! \brief Generates a random number in the range [-1, 1) using std::rand
	//! \ingroup ionCore
	static inline float nrand()
	{
		return (std::rand() / (float) RAND_MAX) * 2.f - 1.f;
	}

	//! \brief Helper methods for generating random numbers
	//! \ingroup ionCore
	class Random
	{

	public:

		static float Between(float const Min, float const Max)
		{
			return frand() * (Max - Min) + Min;
		}

		static int Between(int const Min, int const Max)
		{
			if (Min == Max)
			{
				return Min;
			}
			else
			{
				return std::rand() % (Max - Min) + Min;
			}
		}

	};

}
