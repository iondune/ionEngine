
#pragma once

#include <ionCore.h>
#include "SRange.h"


namespace ion
{

	template <typename T>
	class IDatabase
	{

	public:

		virtual void AddField(std::string const & Field) = 0;
		virtual bool HasField(std::string const & Field) = 0;

		virtual SRange<T> GetFieldRange(std::string const & Field, T const OutlierCutoff = 5, SRange<T> const & acceptedValues = SRange<T>::Full) const = 0;

	};

}
