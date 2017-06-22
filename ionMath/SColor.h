
#pragma once

#include <ionCore.h>
#include "SVector.h"


namespace Color
{

	//! \brief Determines the maximum color value for a given type
	//! \ingroup ionMath
	template <typename T>
	struct Full
	{};

	template <>
	struct Full<float>
	{
		static float Value()
		{
			return 1.f;
		}
	};

	template <>
	struct Full<ion::byte>
	{
		static byte Value()
		{
			return 255;
		}
	};

	//! \brief Implements a conversion between two color types
	//! \ingroup ionMath
	template <typename T, typename U>
	struct Convert
	{};

	template <>
	struct Convert<ion::byte, float>
	{
		static byte From(float const Value)
		{
			return ion::Clamp((ion::uint) roundf(Value * 255.f), 0u, 255u);
		}
	};

	template <>
	struct Convert<float, byte>
	{
		static float From(byte const Value)
		{
			return ion::Clamp((float) Value / 255.f, 0.f, 1.f);
		}
	};

}

template <typename T>
class SColorA;

//! \brief Customized variant of vec3 that intelligently handles conversion between floating point and integer colors
//! \ingroup ionMath
template <typename T>
class color3 : public ion::vec3<T>
{

public:

	T & Red, & Green, & Blue;

	//! Default constructor
	color3()
		: Red(this->X), Green(this->Y), Blue(this->Z), vec3<T>()
	{}

	//! Scalar constructor
	color3(T const in)
		: Red(this->X), Green(this->Y), Blue(this->Z), vec3<T>(in)
	{}

	//! Explicit constructor
	color3(T const r, T const g, T const b)
		: Red(this->X), Green(this->Y), Blue(this->Z), vec3<T>(r, g, b)
	{}

	//! Copy constructor
	color3(color3<T> const & Other)
		: Red(this->X), Green(this->Y), Blue(this->Z), vec3<T>(Other)
	{}

	//! Vector copy constructor
	color3(vec3<T> const & Other)
		: Red(this->X), Green(this->Y), Blue(this->Z), vec3<T>(Other)
	{}

	//! Generic copy constructor
	template <typename U>
	color3(color3<U> const & Other)
		: Red(this->X), Green(this->Y), Blue(this->Z), vec3<T>()
	{
		Red = Color::Convert<T, U>::From(Other.Red);
		Green = Color::Convert<T, U>::From(Other.Green);
		Blue = Color::Convert<T, U>::From(Other.Blue);
	}

	//! Copy assignment operator
	color3<T> & operator = (color3<T> const & Other)
	{
		Red = Other.Red;
		Green = Other.Green;
		Blue = Other.Blue;
		return * this;
	}

	//! Generic copy assignment operator
	template <typename U>
	color3<T> & operator = (color3<U> const & Other)
	{
		Red = Color::Convert<T, U>::From(Other.Red);
		Green = Color::Convert<T, U>::From(Other.Green);
		Blue = Color::Convert<T, U>::From(Other.Blue);
		return *this;
	}

};


//! \brief Customized variant of vec4 that intelligently handles conversion between floating point and integer colors
//! \ingroup ionMath
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

	//! Scalar constructor
	SColorA(color3<T> const & Other)
		: Red(Values[0]), Green(Values[1]), Blue(Values[2]), Alpha(Values[3])
	{
		Red = Other.Red;
		Green = Other.Green;
		Blue = Other.Blue;
		Alpha = Color::Full<T>::Value();
	}

	SColorA<T> & operator = (SColorA<T> const & vec)
	{
		set(vec);

		return * this;
	}

	template <typename U, int OtherDimension>
	SColorA<T> & operator = (SVectorBase<U, OtherDimension> const & vec)
	{
		set(vec);

		return * this;
	}

	SColorA<T> & operator = (color3<T> const & col)
	{
		Red = col.Red;
		Green = col.Green;
		Blue = col.Blue;
		Alpha = Color::Full<T>::Value();

		return * this;
	}

	template <typename U>
	SColorA<T> & operator = (color3<U> const & col)
	{
		Red = Color::Convert<T, U>::From(col.Red);
		Green = Color::Convert<T, U>::From(col.Green);
		Blue = Color::Convert<T, U>::From(col.Blue);
		Alpha = Color::Full<T>::Value();

		return * this;
	}

	template <typename U, int OtherDimension>
	void set(SVectorBase<U, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	template <int OtherDimension>
	void set(SVectorBase<ion::byte, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	template <int OtherDimension>
	void set(SVectorBase<float, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	template <int OtherDimension>
	void set(SVectorBase<double, OtherDimension> const & other)
	{
		for (int i = 0; i < 4; ++ i)
			Values[i] = (T) other[i];
	}

	operator color3<T>()
	{
		color3<T> ret;
		ret.Red = Red;
		ret.Green = Green;
		ret.Blue = Blue;
		return ret;
	}

};

template <typename T>
T const SColorA<T>::Full = 1;

template <>
template <int OtherDimension>
void SColorA<float>::set(SVectorBase<ion::byte, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (float) other[i] / 255.f;
}

template <>
template <int OtherDimension>
void SColorA<double>::set(SVectorBase<ion::byte, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (double) other[i] / 255.0;
}

template <>
template <int OtherDimension>
void SColorA<ion::byte>::set(SVectorBase<float, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (ion::byte) (other[i] * 255);
}

template <>
template <int OtherDimension>
void SColorA<ion::byte>::set(SVectorBase<double, OtherDimension> const & other)
{
	for (int i = 0; i < 4; ++ i)
		Values[i] = (ion::byte) (other[i] * 255);
}


typedef color3<ion::byte> SColori;
typedef color3<ion::byte> SColorc;
typedef SColorA<ion::byte> SColorAi;
typedef SColorA<ion::byte> SColorAc;
typedef color3<ion::byte> SColor24;
typedef SColorA<ion::byte> SColor32;

typedef color3<float> SColorf;
typedef SColorA<float> SColorAf;
typedef color3<float> SColor72;
typedef SColorA<float> SColor96;

typedef color3<double> SColord;
typedef SColorA<double> SColorAd;
typedef color3<double> SColor192;
typedef SColorA<double> SColor256;

typedef SColori color3i;
typedef SColorf color3f;
typedef SColorAi color4i;
typedef SColorAf color4f;


//! \brief Some very basic colors
//! \ingroup ionMath
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

namespace Color
{

	//! \brief Packs a color into 24 bits
	//! \ingroup ionMath
	struct Pack
	{

		static ion::uint Bits24(color3i const & Color)
		{
			ion::uint const Red = Color.Red;
			ion::uint const Green = Color.Green;
			ion::uint const Blue = Color.Blue;
			return (Red << 16) | (Green << 8) | (Blue);
		}

	};

	//! \brief Unacks a color from 24 bits
	//! \ingroup ionMath
	struct Unpack
	{

		static color3i Bits24(ion::uint const Value)
		{
			color3i Color;
			Color.Red = (Value >> 16) & 0xFF;
			Color.Green = (Value >> 8) & 0xFF;
			Color.Blue = Value & 0xFF;
			return Color;
		}

	};

}
