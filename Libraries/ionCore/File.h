
#pragma once

#include "ionTypes.h"

#include <fstream>


namespace ion
{

	//! \brief Helper methods for dealing with files
	//! \ingroup ionCore
	class File
	{

	public:

		static bool Exists(string const & FileName);

		static bool IsDirectory(string const & FileName);
		static bool IsFile(string const & FileName);

		static string ReadAsString(string const & FileName);

		static string StripExtension(string const & Path);

		static string GetExtension(string const & Path);

	};

}
