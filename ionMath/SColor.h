
#pragma once

#include "SVector.h"
#include "SVector3.h"


namespace Color
{

	template <typename T>
	struct Full
	{};

	template <>
	struct Full<f32>
	{
		static f32 Value()
		{
			return 1.f;
		}
	};

	template <>
	struct Full<u8>
	{
		static u8 Value()
		{
			return 255;
		}
	};

	template <typename T, typename U>
	struct Convert
	{};

	template <>
	struct Convert<u8, f32>
	{
		static u8 From(f32 const Value)
		{
			return Clamp((uint) roundf(Value * 255.f), 0u, 255u);
		}
	};

	template <>
	struct Convert<f32, u8>
	{
		static f32 From(u8 const Value)
		{
			return Clamp((float) Value / 255.f, 0.f, 1.f);
		}
	};

}

template <typename T>
class SColorA;

template <typename T>
class color3 : public vec3<T>
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

	template <typename U, u32 OtherDimension>
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


typedef color3<u8> SColori;
typedef color3<u8> SColorc;
typedef SColorA<u8> SColorAi;
typedef SColorA<u8> SColorAc;
typedef color3<u8> SColor24;
typedef SColorA<u8> SColor32;

typedef color3<f32> SColorf;
typedef SColorA<f32> SColorAf;
typedef color3<f32> SColor72;
typedef SColorA<f32> SColor96;

typedef color3<f64> SColord;
typedef SColorA<f64> SColorAd;
typedef color3<f64> SColor192;
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

namespace Color
{

	struct Pack
	{

		static uint Bits24(color3i const & Color)
		{
			uint const Red = Color.Red;
			uint const Green = Color.Green;
			uint const Blue = Color.Blue;
			return (Red << 16) | (Green << 8) | (Blue);
		}

	};

	struct Unpack
	{

		static color3i Bits24(uint const Value)
		{
			color3i Color;
			Color.Red = (Value >> 16) & 0xFF;
			Color.Green = (Value >> 8) & 0xFF;
			Color.Blue = Value & 0xFF;
			return Color;
		}

	};

}
