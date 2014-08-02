
#pragma once

#include "ionTypes.h"

#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

using std::move;

using std::ifstream;
using std::ofstream;
using std::stringstream;

using std::cout;
using std::cerr;
using std::endl;


template <typename T, typename U>
U * ConditionalMapAccess(map<T, U *> & Map, T const Key)
{
	auto Iterator = Map.find(Key);

	if (Iterator != Map.end())
		return Iterator->second;

	return 0;
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
