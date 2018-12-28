
#pragma once

#include <ionCore.h>


namespace ion
{

	class Directory
	{

	public:

		static vector<string> Read(string const & Path);
		static vector<string> FindByExtension(string const & Path, string const & Extension);

	};

}
