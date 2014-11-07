
#pragma once

#include <ionConfig.h>
#include "ionTypes.h"

#include <cstdlib>


static f32 frand()
{
	return std::rand() / (f32) RAND_MAX;
}

static f32 nrand()
{
	return (std::rand() / (f32) RAND_MAX) * 2.f - 1.f;
}

class IRandomGenerator
{

public:

	virtual u32 const Generate() = 0;
	virtual void Seed(u32 const seed) = 0;

	u32 const Generate(u32 const max)
	{
		return Generate() % max;
	}

	u32 const Generate(u32 const min, u32 const max)
	{
		return Generate() % (max - min) + min;
	}

	f32 const Generatef32(u32 const modulus = 100000)
	{
		return (Generate() % modulus) / (f32) modulus;
	}

	f32 const Generatef32(f32 const max, u32 const modulus = 100000)
	{
		return Generatef32(modulus) * max;
	}

	f32 const Generatef32(f32 const min, f32 const max, u32 const modulus = 100000)
	{
		return Generatef32(modulus) * (max - min) + min;
	}

	f64 const Generatef64(u32 const modulus = 100000)
	{
		return (Generate() % modulus) / (f64) modulus;
	}

	f64 const Generatef64(f64 const max, u32 const modulus = 100000)
	{
		return Generatef64(modulus) * max;
	}

	f64 const Generatef64(f64 const min, f64 const max, u32 const modulus = 100000)
	{
		return Generatef64(modulus) * (max - min) + min;
	}

};

class CLinearCongruentialGenerator : public IRandomGenerator
{

	u32 Value;

public:

	CLinearCongruentialGenerator(u32 const seed = 0)
	{
		Seed(seed);
	}

	u32 const Generate()
	{
		return (Value = (Value * 214013 + 2531011) & ((1U << 31) - 1));
	}

	void Seed(u32 const seed)
	{
		Value = seed;
	}

};
