
#include "ionDirectory.h"
#include <dirent.h>


vector<string> Directory::Read(string const & Path)
{
	vector<string> Files;

	DIR * dir = opendir(Path.c_str());
	if (dir)
	{
		dirent * ent;
		while ((ent = readdir(dir)))
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

vector<string> Directory::FindByExtension(string const & Path, string const & Extension)
{
	vector<string> FoundFiles;
	vector<string> const Files = Directory::Read(Path);

	for (auto const & FileName : Files)
	{
		if (FileName == "." || FileName == ".." || FileName.find('.') == std::string::npos)
			continue;

		std::string const ThisFileExtension = FileName.substr(FileName.find_last_of('.'));
		if (ThisFileExtension == ("." + Extension))
		{
			FoundFiles.push_back(FileName);
		}
	}

	return FoundFiles;
}
