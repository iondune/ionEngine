
#pragma once

#include "SVector.h"


template <typename T>
class SColorA;

template <typename T>
class SColor : public SVector<T, 3, SColor<T> >
{

public:

	using SVectorBase<T, 3>::set;
	using SVectorBase<T, 3>::Values;

	T & Red, & Green, & Blue;
	static T const Full;

	SColor()
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		set((T) 0);
	}

	SColor(T const in)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		set(in);
	}

	SColor(T const r, T const g, T const b)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		Values[0] = r;
		Values[1] = g;
		Values[2] = b;
	}

	SColor(SColor<T> const & vec)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		set(vec);
	}

	template <typename U, u32 OtherDimension>
	SColor(SVectorBase<U, OtherDimension> const & vec)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2])
	{
		set(vec);
	}

	SColor<T> & operator = (SColor<T> const & vec)
	{
		set(vec);

		return * this;
	}

	template <typename U, u32 OtherDimension>
	SColor<T> & operator = (SVectorBase<U, OtherDimension> const & vec)
	{
		set(vec);

		return * this;
	}

	virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < 3 ? Values[i] : (i == 3 ? SVectorBase<T, 3>::OutOfBounds = Full : SVectorBase<T, 3>::OutOfBounds = 0));
	}

	virtual T & operator[] (int i)
	{
		return (i >= 0 && i < 3 ? Values[i] : (i == 3 ? SVectorBase<T, 3>::OutOfBounds = Full : SVectorBase<T, 3>::OutOfBounds = 0));
	}

	template <typename U, u32 OtherDimension>
	void set(SVectorBase<U, OtherDimension> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			Values[i] = (T) other[i];
	}

	template <u32 OtherDimension>
	void set(SVectorBase<u8, OtherDimension> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			Values[i] = (T) other[i];
	}

	template <u32 OtherDimension>
	void set(SVectorBase<f32, OtherDimension> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			Values[i] = (T) other[i];
	}

	template <u32 OtherDimension>
	void set(SVectorBase<f64, OtherDimension> const & other)
	{
		for (int i = 0; i < 3; ++ i)
			Values[i] = (T) other[i];
	}

};

template <typename T>
T const SColor<T>::Full = 1;

template <>
template <u32 OtherDimension>
void SColor<f32>::set(SVectorBase<u8, OtherDimension> const & other)
{
	for (u32 i = 0; i < 3; ++ i)
		Values[i] = (f32) other[i] / 255.f;
}

template <>
template <u32 OtherDimension>
void SColor<f64>::set(SVectorBase<u8, OtherDimension> const & other)
{
	for (u32 i = 0; i < 3; ++ i)
		Values[i] = (f64) other[i] / 255.0;
}

template <>
template <u32 OtherDimension>
void SColor<u8>::set(SVectorBase<f32, OtherDimension> const & other)
{
	for (u32 i = 0; i < 3; ++ i)
		Values[i] = (u8) (other[i] * 255);
}

template <>
template <u32 OtherDimension>
void SColor<u8>::set(SVectorBase<f64, OtherDimension> const & other)
{
	for (u32 i = 0; i < 3; ++ i)
		Values[i] = (u8) (other[i] * 255);
}


template <typename T>
class SColorA : public SVector<T, 4, SColorA<T> >
{

public:

	using SVectorBase<T, 4>::set;
	using SVectorBase<T, 4>::Values;

	T & Red, & Green, & Blue, & Alpha;
	static T const Full;

	SColorA()
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		set((T) 0);
	}

	SColorA(T const in)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		set(in);
	}

	SColorA(T const r, T const g, T const b, T const a = Full)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		Values[0] = r;
		Values[1] = g;
		Values[2] = b;
		Values[3] = a;
	}

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

	template <typename U, u32 OtherDimension>
	SColorA<T> & operator = (SVectorBase<U, OtherDimension> const & vec)
	{
		set(vec);

		return * this;
	}

	template <typename U, u32 OtherDimension>
	void set(SVectorBase<U, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	template <u32 OtherDimension>
	void set(SVectorBase<u8, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	template <u32 OtherDimension>
	void set(SVectorBase<f32, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	template <u32 OtherDimension>
	void set(SVectorBase<f64, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

};

template <typename T>
T const SColorA<T>::Full = 1;

template <>
template <u32 OtherDimension>
void SColorA<f32>::set(SVectorBase<u8, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (f32) other[i] / 255.f;
}

template <>
template <u32 OtherDimension>
void SColorA<f64>::set(SVectorBase<u8, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (f64) other[i] / 255.0;
}

template <>
template <u32 OtherDimension>
void SColorA<u8>::set(SVectorBase<f32, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (u8) (other[i] * 255);
}

template <>
template <u32 OtherDimension>
void SColorA<u8>::set(SVectorBase<f64, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (u8) (other[i] * 255);
}


typedef SColor<u8> SColori;
typedef SColor<u8> SColorc;
typedef SColorA<u8> SColorAi;
typedef SColorA<u8> SColorAc;
typedef SColor<u8> SColor24;
typedef SColorA<u8> SColor32;

typedef SColor<f32> SColorf;
typedef SColorA<f32> SColorAf;
typedef SColor<f32> SColor72;
typedef SColorA<f32> SColor96;

typedef SColor<f64> SColord;
typedef SColorA<f64> SColorAd;
typedef SColor<f64> SColor192;
typedef SColorA<f64> SColor256;

typedef SColori color3i;
typedef SColorf color3f;
typedef SColorAi color4i;
typedef SColorAf color4f;


namespace Colors
{
	static color3f const White = color3f(1, 1, 1);
	static color3f const Black = color3f(0, 0, 0);
	static color3f const Red = color3f(1, 0, 0);
	static color3f const Orange = color3f(1, 0.5f, 0);
	static color3f const Yellow = color3f(1, 1, 0);
	static color3f const Green = color3f(0, 1, 0);
	static color3f const Cyan = color3f(0, 1, 1);
	static color3f const Blue = color3f(0, 0, 1);
	static color3f const Magenta = color3f(1, 0, 1);
}
