
#pragma once

#include <ionCore/ionTypes.h>


namespace Constants32
{

	f32 const Pi = 3.14159265359f;
	f32 const e =  2.71828182845f;

};

namespace Constants64
{

	f64 const Pi = 3.141592653589793238462643383279;
	f64 const e =  2.718281828459045235360287471352;

};

template <typename T>
struct Constants
{
/*	static T const Pi()
	{
		return 0;
	}
	static T const e()
	{
		return 0;
	}*/
};

template <>
struct Constants<f32>
{
	static f32 Pi()
	{
		return Constants32::Pi;
	}
	static f32 e()
	{
		return Constants32::e;
	}
};

template <>
struct Constants<f64>
{
	static f64 Pi()
	{
		return Constants64::Pi;
	}
	static f64 e()
	{
		return Constants64::e;
	}
};
