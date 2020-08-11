
#include "File.h"

#include <iterator>
#include <filesystem>


namespace ion
{

	bool File::Exists(string const & FileName)
	{
		return std::filesystem::exists(FileName);
	}

	bool File::IsDirectory(string const & FileName)
	{
		std::filesystem::path p(FileName);
		std::filesystem::file_status s = std::filesystem::status(p);
		return std::filesystem::status_known(s) && s.type() == std::filesystem::file_type::directory;
	}

	bool File::IsFile(string const & FileName)
	{
		std::filesystem::path p(FileName);
		std::filesystem::file_status s = std::filesystem::status(p);
		return std::filesystem::status_known(s) && s.type() == std::filesystem::file_type::regular;
	}

	string File::ReadAsString(string const & FileName)
	{
		std::ifstream FileHandle(FileName);
		std::string String;

		FileHandle.seekg(0, std::ios::end);
		String.reserve((uint) FileHandle.tellg());
		FileHandle.seekg(0, std::ios::beg);

		String.assign((std::istreambuf_iterator<char>(FileHandle)), std::istreambuf_iterator<char>());

		return String;
	}

	string File::StripExtension(string const & Path)
	{
		return Path.substr(0, Path.find_last_of("."));
	}

	string File::GetExtension(string const & Path)
	{
		size_t Index = Path.find_last_of(".");
		if (Index == string::npos)
		{
			return "";
		}
		else
		{
			return Path.substr(Index + 1);
		}
	}

}
