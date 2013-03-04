#ifndef _CABBAGE_CORE_SCOLOR_H_INCLUDED_
#define _CABBAGE_CORE_SCOLOR_H_INCLUDED_

#include "SVector.h"


template <typename T>
class SColorA;

template <typename T>
class SColor : public SVector<T, 3, SColor<T> >
{

public:

	T & Red, & Green, & Blue;
	static T const Full;

	SColor()
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		SVectorSimple<T, 3>::set((T) 0);
	}

	SColor(T const in)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		SVectorSimple<T, 3>::set(in);
	}

	SColor(T const r, T const g, T const b)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		this->Values[0] = r;
		this->Values[1] = g;
		this->Values[2] = b;
	}

	SColor(T const & r, T const & g, T const & b, ForceReference)
		: Red(r), Green(g), Blue(b)
	{}

	SColor(SColor<T> const & vec)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		set(vec);
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SColor(SVector<U, otherDimension, otherImplementation> const & vec)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		set(vec);
	}

	SColor<T> & operator = (SColor<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SColor<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(vec);

		return * this;
	}

	virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < 3 ? this->Values[i] : (i == 3 ? SVectorSimple<T, 3>::OutOfBounds = Full : SVectorSimple<T, 3>::OutOfBounds = 0));
	}

	virtual T & operator[] (int i)
	{
		return (i >= 0 && i < 3 ? this->Values[i] : (i == 3 ? SVectorSimple<T, 3>::OutOfBounds = Full : SVectorSimple<T, 3>::OutOfBounds = 0));
	}

	template <typename U, int otherDimension, typename otherImplementation>
	void set(SVector<U, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <int otherDimension, typename otherImplementation>
	void set(SVector<unsigned char, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <int otherDimension, typename otherImplementation>
	void set(SVector<float, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <int otherDimension, typename otherImplementation>
	void set(SVector<double, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			this->Values[i] = (T) other[i];
	}

};

template <typename T>
T const SColor<T>::Full = 1;

template <>
unsigned char const SColor<unsigned char>::Full = 255;

template <>
template <int otherDimension, typename otherImplementation>
void SColor<float>::set(SVector<unsigned char, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 3; ++ i)
		this->Values[i] = (float) other[i] / 255.f;
}

template <>
template <int otherDimension, typename otherImplementation>
void SColor<double>::set(SVector<unsigned char, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 3; ++ i)
		this->Values[i] = (double) other[i] / 255.0;
}

template <>
template <int otherDimension, typename otherImplementation>
void SColor<unsigned char>::set(SVector<float, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 3; ++ i)
		this->Values[i] = (unsigned char) (other[i] * 255);
}

template <>
template <int otherDimension, typename otherImplementation>
void SColor<unsigned char>::set(SVector<double, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 3; ++ i)
		this->Values[i] = (unsigned char) (other[i] * 255);
}


template <typename T>
class SColorA : public SVector<T, 4, SColor<T> >
{

public:

	T & Red, & Green, & Blue, & Alpha;
	static T const Full;

	SColorA()
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		SVectorSimple<T, 4>::set((T) 0);
	}

	SColorA(T const in)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		SVectorSimple<T, 4>::set(in);
	}

	SColorA(T const r, T const g, T const b, T const a = Full)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		this->Values[0] = r;
		this->Values[1] = g;
		this->Values[2] = b;
		this->Values[3] = a;
	}

	SColorA(T const & r, T const & g, T const & b, T const & a, ForceReference)
		: Red(r), Green(g), Blue(b), Alpha(a)
	{}

	SColorA(SColorA<T> const & vec)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		set(vec);
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SColorA(SVector<U, otherDimension, otherImplementation> const & vec)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		set(vec);
	}

	SColorA<T> & operator = (SColorA<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SColorA<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(vec);

		return * this;
	}

	virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < 4 ? this->Values[i] : SVectorSimple<T, 4>::OutOfBounds = 0);
	}

	virtual T & operator[] (int i)
	{
		return (i >= 0 && i < 4 ? this->Values[i] : SVectorSimple<T, 4>::OutOfBounds = 0);
	}

	template <typename U, int otherDimension, typename otherImplementation>
	void set(SVector<U, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <int otherDimension, typename otherImplementation>
	void set(SVector<unsigned char, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <int otherDimension, typename otherImplementation>
	void set(SVector<float, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <int otherDimension, typename otherImplementation>
	void set(SVector<double, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			this->Values[i] = (T) other[i];
	}

};

template <typename T>
T const SColorA<T>::Full = 1;

template <>
unsigned char const SColorA<unsigned char>::Full = 255;

template <>
template <int otherDimension, typename otherImplementation>
void SColorA<float>::set(SVector<unsigned char, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 4; ++ i)
		this->Values[i] = (float) other[i] / 255.f;
}

template <>
template <int otherDimension, typename otherImplementation>
void SColorA<double>::set(SVector<unsigned char, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 4; ++ i)
		this->Values[i] = (double) other[i] / 255.0;
}

template <>
template <int otherDimension, typename otherImplementation>
void SColorA<unsigned char>::set(SVector<float, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 4; ++ i)
		this->Values[i] = (unsigned char) (other[i] * 255);
}

template <>
template <int otherDimension, typename otherImplementation>
void SColorA<unsigned char>::set(SVector<double, otherDimension, otherImplementation> const & other)
{
	for (int i = 0; i < 4; ++ i)
		this->Values[i] = (unsigned char) (other[i] * 255);
}


typedef SColor<unsigned char> SColori;
typedef SColor<unsigned char> SColorc;
typedef SColorA<unsigned char> SColorAi;
typedef SColorA<unsigned char> SColorAc;
typedef SColor<unsigned char> SColor24;
typedef SColorA<unsigned char> SColor32;

typedef SColor<float> SColorf;
typedef SColorA<float> SColorAf;
typedef SColor<float> SColor72;
typedef SColorA<float> SColor96;

typedef SColor<double> SColord;
typedef SColorA<double> SColorAd;
typedef SColor<double> SColor192;
typedef SColorA<double> SColor256;


namespace Colors
{
	static SColorAf const White = SColorAf(1.f, 1.f, 1.f, 1.f);
	static SColorAf const Black = SColorAf(0.f, 0.f, 0.f, 1.f);
}

#endif
