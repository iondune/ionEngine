#ifndef _ION_CORE_H_INCLUDED_
#define _ION_CORE_H_INCLUDED_

#include "ionConfig.h"


class IRandomGenerator
{

public:

	virtual unsigned int const generate() = 0;
	virtual void seed(unsigned int const seed) = 0;

	unsigned int const generate(unsigned int const max)
	{
		return generate() % max;
	}

	unsigned int const generate(unsigned int const min, unsigned int const max)
	{
		return generate() % (max - min) + min;
	}

	float const generateFloat(unsigned int const modulus = 100000)
	{
		return (generate() % modulus) / (float) modulus;
	}

	float const generateFloat(float const max, unsigned int const modulus = 100000)
	{
		return generateFloat(modulus) * max;
	}

	float const generateFloat(float const min, float const max, unsigned int const modulus = 100000)
	{
		return generateFloat(modulus) * (max - min) + min;
	}

	double const generateDouble(unsigned int const modulus = 100000)
	{
		return (generate() % modulus) / (double) modulus;
	}

	double const generateDouble(double const max, unsigned int const modulus = 100000)
	{
		return generateDouble(modulus) * max;
	}

	double const generateDouble(double const min, double const max, unsigned int const modulus = 100000)
	{
		return generateDouble(modulus) * (max - min) + min;
	}

};


class CLinearCongruentialGenerator
{

	unsigned int Seed;

public:

	CLinearCongruentialGenerator()
	{
		seed(0);
	}

	unsigned int const generate()
	{
		return (Seed = (Seed * 214013 + 2531011) & ((1U << 31) - 1));
	}

	void seed(unsigned int const seed)
	{
		Seed = seed;
	}

};

#endif
