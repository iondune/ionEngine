
/*!
\file ionRand.h
\ingroup ionCore
\brief Random number generators and helpers.
*/


#pragma once

#include <ionConfig.h>
#include "ionTypes.h"

#include <cstdlib>


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
		return std::rand() % (Max - Min) + Min;
	}

};

//! \brief Interface for random number generation
//! \ingroup ionCore
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

//! \brief Basic LCG implementation
//! \ingroup ionCore
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
