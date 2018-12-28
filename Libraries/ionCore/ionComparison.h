
/*!
\file ionClass.h
\ingroup ionCore
\brief Methods and classes for performing comparisons between numbers.
*/

#pragma once

#include "ionTypes.h"


namespace ion
{

	////////////////////
	// Rounding Error //
	////////////////////

	//! \brief Global constant for 32bit floating-point epsilon
	//! \ingroup ionCore
	float const RoundingError32 = 0.00001f;

	//! \brief Global constant for 64bit floating-point epsilon
	//! \ingroup ionCore
	double const RoundingError64 = 0.00000001;

	//! \brief Helper template to enable template-dependant epsilon values
	//! \ingroup ionCore
	//! \tparam T Type of number to retrieve epsilon value
	template <typename T>
	struct RoundingError
	{
		static T const Value()
		{
			return 0;
		}
	};

	//! \brief Template specialization of RoundingError for 32bit floating-point values
	//! \ingroup ionCore
	template <>
	struct RoundingError<float>
	{
		static float Value()
		{
			return RoundingError32;
		}
	};

	//! \brief Template specialization of RoundingError for 64bit floating-point values
	//! \ingroup ionCore
	template <>
	struct RoundingError<double>
	{
		static double Value()
		{
			return RoundingError64;
		}
	};


	//////////////
	// Equality //
	//////////////

	//! \brief Template function for comparing two values for equality within an epsilon range
	//! \ingroup ionCore
	template <typename T>
	static inline bool Equals(T const a, T const b, T const epsilon = RoundingError<T>::Value())
	{
		return (a + epsilon >= b) && (a - epsilon <= b);
	}


	////////////////
	// Comparison //
	////////////////

	//! \brief Template function for selecting the minimum of two values
	//! \ingroup ionCore
	template <typename T>
	static inline T Minimum(T const & a, T const & b)
	{
		return a < b ? a : b;
	}

	//! \brief Template function for selecting the maximum of two values
	//! \ingroup ionCore
	template <typename T>
	static inline T Maximum(T const & a, T const & b)
	{
		return b < a ? a : b;
	}

	//! \brief Template function for selecting the minimum of three values
	//! \ingroup ionCore
	template <typename T>
	static inline T Minimum(T const & a, T const & b, T const & c)
	{
		return Minimum(a, Minimum(b, c));
	}

	//! \brief Template function for selecting the maximum of three values
	//! \ingroup ionCore
	template <typename T>
	static inline T Maximum(T const & a, T const & b, T const & c)
	{
		return Maximum(a, Maximum(b, c));
	}

	//! \brief Template function for selecting the minimum of four values
	//! \ingroup ionCore
	template <typename T>
	static inline T Minimum(T const & a, T const & b, T const & c, T const & d)
	{
		return Minimum(a, Minimum(b, c, d));
	}

	//! \brief Template function for selecting the maximum of four values
	//! \ingroup ionCore
	template <typename T>
	static inline T Maximum(T const & a, T const & b, T const & c, T const & d)
	{
		return Maximum(a, Maximum(b, c, d));
	}


	//! \brief Template function for selecting the minimum of two values
	//! \ingroup ionCore
	template <typename T>
	static inline T Min(T const & a, T const & b)
	{
		return a < b ? a : b;
	}

	//! \brief Template function for selecting the maximum of two values
	//! \ingroup ionCore
	template <typename T>
	static inline T Max(T const & a, T const & b)
	{
		return b < a ? a : b;
	}

	//! \brief Template function for selecting the minimum of three values
	//! \ingroup ionCore
	template <typename T>
	static inline T Min(T const & a, T const & b, T const & c)
	{
		return Min(a, Min(b, c));
	}

	//! \brief Template function for selecting the maximum of three values
	//! \ingroup ionCore
	template <typename T>
	static inline T Max(T const & a, T const & b, T const & c)
	{
		return Max(a, Max(b, c));
	}

	//! \brief Template function for selecting the minimum of four values
	//! \ingroup ionCore
	template <typename T>
	static inline T Min(T const & a, T const & b, T const & c, T const & d)
	{
		return Min(a, Min(b, c, d));
	}

	//! \brief Template function for selecting the maximum of four values
	//! \ingroup ionCore
	template <typename T>
	static inline T Max(T const & a, T const & b, T const & c, T const & d)
	{
		return Max(a, Max(b, c, d));
	}

}
