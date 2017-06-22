
#pragma once

#include "ionTypes.h"


namespace ion
{

	//! \ingroup ionCore
	namespace Constants32
	{

		float const Pi = 3.14159265359f;
		float const e = 2.71828182845f;

	};

	//! \ingroup ionCore
	namespace Constants64
	{

		double const Pi = 3.141592653589793238462643383279;
		double const e = 2.718281828459045235360287471352;

	};

	//! \brief Template-friendly access to Constants32 or Constants64
	//! \ingroup ionCore
	template <typename T>
	struct Constants
	{};

	template <>
	struct Constants<float>
	{
		static float Pi()
		{
			return Constants32::Pi;
		}
		static float e()
		{
			return Constants32::e;
		}
	};

	template <>
	struct Constants<double>
	{
		static double Pi()
		{
			return Constants64::Pi;
		}
		static double e()
		{
			return Constants64::e;
		}
	};

}
