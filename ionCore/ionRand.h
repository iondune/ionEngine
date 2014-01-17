
#pragma once

#include <ionConfig.h>
#include "ionTypes.h"

#include <cstdlib>


ION_FUNC_DEF static f32 frand()
{
	return std::rand() / (f32) RAND_MAX;
}

class IRandomGenerator
{

public:

	virtual u32 const Generate() = 0;
	virtual void Seed(u32 const seed) = 0;

	ION_FUNC_DEF u32 const Generate(u32 const max)
	{
		return Generate() % max;
	}

	ION_FUNC_DEF u32 const Generate(u32 const min, u32 const max)
	{
		return Generate() % (max - min) + min;
	}

	ION_FUNC_DEF f32 const Generatef32(u32 const modulus = 100000)
	{
		return (Generate() % modulus) / (f32) modulus;
	}

	ION_FUNC_DEF f32 const Generatef32(f32 const max, u32 const modulus = 100000)
	{
		return Generatef32(modulus) * max;
	}

	ION_FUNC_DEF f32 const Generatef32(f32 const min, f32 const max, u32 const modulus = 100000)
	{
		return Generatef32(modulus) * (max - min) + min;
	}

	ION_FUNC_DEF f64 const Generatef64(u32 const modulus = 100000)
	{
		return (Generate() % modulus) / (f64) modulus;
	}

	ION_FUNC_DEF f64 const Generatef64(f64 const max, u32 const modulus = 100000)
	{
		return Generatef64(modulus) * max;
	}

	ION_FUNC_DEF f64 const Generatef64(f64 const min, f64 const max, u32 const modulus = 100000)
	{
		return Generatef64(modulus) * (max - min) + min;
	}

};

class CLinearCongruentialGenerator
{

	u32 Value;

public:

	ION_FUNC_DEF CLinearCongruentialGenerator(u32 const seed = 0)
	{
		Seed(seed);
	}

	ION_FUNC_DEF u32 const Generate()
	{
		return (Value = (Value * 214013 + 2531011) & ((1U << 31) - 1));
	}

	ION_FUNC_DEF void Seed(u32 const seed)
	{
		Value = seed;
	}

};
