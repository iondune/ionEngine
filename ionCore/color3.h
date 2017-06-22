
#pragma once

#include "vec3.h"
#include "ionUtils.h"


namespace ion
{

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
		struct Full<byte>
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
		struct Convert<byte, float>
		{
			static byte From(float const Value)
			{
				return Clamp((uint) roundf(Value * 255.f), 0u, 255u);
			}
		};

		template <>
		struct Convert<float, byte>
		{
			static float From(byte const Value)
			{
				return Clamp((float) Value / 255.f, 0.f, 1.f);
			}
		};

	}

	//! \brief Customized variant of vec3 that intelligently handles conversion between floating point and integer colors
	//! \ingroup ionMath
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


	typedef color3<byte> color3i;
	typedef color3<float> color3f;

}
