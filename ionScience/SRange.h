
#pragma once

#include <ionCore/ionTypes.h>


template <typename T>
struct SRange
{
	static SRange const Full;
	static SRange const Empty;

	bool Contains(T const value) const
	{
		return value >= Minimum && value <= Maximum;
	}

	bool IsEmpty() const
	{
		return Minimum > Maximum;
	}

	SRange()
	{
		* this = Empty;
	}

	SRange(T const minimum, T const maximum)
		: Minimum(minimum), Maximum(maximum)
	{}

	SRange & operator = (SRange const & Other)
	{
		Minimum = Other.Minimum;
		Maximum = Other.Maximum;
		return * this;
	}

	T Minimum;
	T Maximum;
};

template <typename T>
SRange<T> const SRange<T>::Full = SRange<T>(-std::numeric_limits<T>::max(), std::numeric_limits<T>::max());

template <typename T>
SRange<T> const SRange<T>::Empty = SRange<T>(std::numeric_limits<T>::max(), -std::numeric_limits<T>::max());
