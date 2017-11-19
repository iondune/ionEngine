
#pragma once

#include "vec4.h"
#include "color3.h"


namespace ion
{

	//! \brief Customized variant of vec4 that intelligently handles conversion between floating point and integer colors
	//! \ingroup ionCore
	template <typename T>
	class color4 : public vec4<T>
	{

	public:

		T & Red, & Green, & Blue, & Alpha;

		//! Default constructor
		color4()
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>()
		{}

		//! Scalar constructor
		color4(T const in)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>(in)
		{}

		//! Explicit constructor
		color4(T const r, T const g, T const b, T const a)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>(r, g, b, a)
		{}

		//! Copy constructor
		color4(color4<T> const & Other)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>(Other)
		{}

		//! Vector copy constructor
		color4(vec4<T> const & Other)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>(Other)
		{}

		//! Generic copy constructor
		template <typename U>
		color4(color4<U> const & Other)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>()
		{
			Red = Color::Convert<T, U>::From(Other.Red);
			Green = Color::Convert<T, U>::From(Other.Green);
			Blue = Color::Convert<T, U>::From(Other.Blue);
			Alpha = Color::Convert<T, U>::From(Other.Alpha);
		}

		//! Copy assignment operator
		color4<T> & operator = (color4<T> const & Other)
		{
			Red = Other.Red;
			Green = Other.Green;
			Blue = Other.Blue;
			Alpha = Other.Alpha;
			return * this;
		}

		//! Generic copy assignment operator
		template <typename U>
		color4<T> & operator = (color4<U> const & Other)
		{
			Red = Color::Convert<T, U>::From(Other.Red);
			Green = Color::Convert<T, U>::From(Other.Green);
			Blue = Color::Convert<T, U>::From(Other.Blue);
			Alpha = Color::Convert<T, U>::From(Other.Alpha);
			return *this;
		}

		//! color3 constructor
		color4(color3<T> const & Other)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>(Other)
		{
			Alpha = Color::Full<T>::Value();
		}

		//! Generic color3 constructor
		template <typename U>
		color4(color3<U> const & Other)
			: Red(this->X), Green(this->Y), Blue(this->Z), Alpha(this->W), vec4<T>()
		{
			Red = Color::Convert<T, U>::From(Other.Red);
			Green = Color::Convert<T, U>::From(Other.Green);
			Blue = Color::Convert<T, U>::From(Other.Blue);
			Alpha = Color::Full<T>::Value();
		}

		//! color3 assignment
		color4<T> & operator = (color3<T> const & col)
		{
			Red = col.Red;
			Green = col.Green;
			Blue = col.Blue;
			Alpha = Color::Full<T>::Value();

			return * this;
		}

		//! Generic color3 assignment
		template <typename U>
		color4<T> & operator = (color3<U> const & col)
		{
			Red = Color::Convert<T, U>::From(col.Red);
			Green = Color::Convert<T, U>::From(col.Green);
			Blue = Color::Convert<T, U>::From(col.Blue);
			Alpha = Color::Full<T>::Value();

			return * this;
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

	typedef color4<byte> color4i;
	typedef color4<float> color4f;

}
