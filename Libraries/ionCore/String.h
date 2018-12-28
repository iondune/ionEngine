
#pragma once

#include "ionTypes.h"

#include <tinyformat.h>
#include <sstream>


namespace ion
{

	//! \brief Helper methods for dealing with strings
	//! \ingroup ionCore
	class String
	{

	public:

		static vector<string> SeparateLines(string const & str);

		static vector<string> Explode(string const & str, char delimiter);

		static bool BeginsWith(string const & s, string const & prefix, string & remainder);

		template <typename... Args>
		static string Build(char const * const Format, Args const &... args)
		{
			return tfm::format(Format, args...);
		}

	};

}
