
#include "ionDirectory.h"
#include <dirent.h>


vector<string> Directory::Read(string const & Path)
{
	vector<string> Files;

	DIR * dir = opendir(Path.c_str());
	if (dir)
	{
		dirent * ent;
		while (ent = readdir(dir))
		{
			std::string const FileName = ent->d_name;
			if (FileName == "." || FileName == "..")
				continue;

			Files.push_back(FileName);
		}
		closedir(dir);
	}

	return Files;
}
