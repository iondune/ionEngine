
#pragma once

#include "ionTypes.h"

#include <algorithm>
#include <numeric>
#include <limits>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>

using std::move;
using std::for_each;

using std::ifstream;
using std::ofstream;
using std::stringstream;

using std::cout;
using std::cerr;
using std::endl;

template <typename T>
using NumericLimits = std::numeric_limits<T>;


template <typename T, typename U>
U * ConditionalMapAccess(map<T, U *> const & Map, T const Key)
{
	auto Iterator = Map.find(Key);

	if (Iterator != Map.end())
		return Iterator->second;

	return 0;
}

template <typename T, typename U>
bool CheckMapAccess(map<T, U> const & Map, T const Key)
{
	return Map.find(Key) != Map.end();
}

template <typename T, typename U>
bool TryMapAccess(map<T, U> const & Map, T const Key, U & Value)
{
	auto Iterator = Map.find(Key);

	if (Iterator != Map.end())
	{
		Value = Iterator->second;
		return true;
	}

	return false;
}

template <typename T>
void AddAtEnd(vector<T> & A, vector<T> const & B)
{
	A.insert(A.end(), B.begin(), B.end());
}

class File
{

public:
	
	static bool Exists(string const & FileName)
	{
	  ifstream ifile(FileName);
	  return ifile.good();
	}

	static string ReadAsString(string const & FileName)
	{
		std::ifstream t(FileName);
		std::string str;

		t.seekg(0, std::ios::end);   
		str.reserve((uint) t.tellg());
		t.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

		return str;
	}

	static vector<string> ReadDirectory(string const & Path)
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
};

class String
{

public:

	static vector<string> SeparateLines(string const & str)
	{
		vector<string> lines;
		stringstream stream(str);
		string line;

		while (std::getline(stream, line))
			lines.push_back(line);

		return lines;
	}

};
