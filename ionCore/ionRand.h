#ifndef _ION_CORE_IONRAND_H_INCLUDED_
#define _ION_CORE_IONRAND_H_INCLUDED_

#include "ionConfig.h"

#include "ionTypes.h"


ION_FUNC_DEF static f32 frand()
{
	return std::rand() / (f32) RAND_MAX;
}

class IRandomGenerator
{

public:

	virtual u32 const generate() = 0;
	virtual void seed(u32 const seed) = 0;

	ION_FUNC_DEF u32 const generate(u32 const max)
	{
		return generate() % max;
	}

	ION_FUNC_DEF u32 const generate(u32 const min, u32 const max)
	{
		return generate() % (max - min) + min;
	}

	ION_FUNC_DEF f32 const generatef32(u32 const modulus = 100000)
	{
		return (generate() % modulus) / (f32) modulus;
	}

	ION_FUNC_DEF f32 const generatef32(f32 const max, u32 const modulus = 100000)
	{
		return generatef32(modulus) * max;
	}

	ION_FUNC_DEF f32 const generatef32(f32 const min, f32 const max, u32 const modulus = 100000)
	{
		return generatef32(modulus) * (max - min) + min;
	}

	ION_FUNC_DEF f64 const generatef64(u32 const modulus = 100000)
	{
		return (generate() % modulus) / (f64) modulus;
	}

	ION_FUNC_DEF f64 const generatef64(f64 const max, u32 const modulus = 100000)
	{
		return generatef64(modulus) * max;
	}

	ION_FUNC_DEF f64 const generatef64(f64 const min, f64 const max, u32 const modulus = 100000)
	{
		return generatef64(modulus) * (max - min) + min;
	}

};

class CLinearCongruentialGenerator
{

	u32 Seed;

public:

	ION_FUNC_DEF CLinearCongruentialGenerator()
	{
		seed(0);
	}

	ION_FUNC_DEF u32 const generate()
	{
		return (Seed = (Seed * 214013 + 2531011) & ((1U << 31) - 1));
	}

	ION_FUNC_DEF void seed(u32 const seed)
	{
		Seed = seed;
	}

};

#endif
