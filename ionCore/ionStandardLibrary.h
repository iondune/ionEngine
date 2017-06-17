
#pragma once

#include "ionTypes.h"
#include "ionSmartPointer.h"

#include <tinyformat.h>

#include <algorithm>
#include <numeric>
#include <limits>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>


using std::move;
using std::for_each;
using std::to_string;

using std::fstream;
using std::ifstream;
using std::ofstream;

using std::stringstream;
using std::istringstream;
using std::ostringstream;

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

	return nullptr;
}

template <typename T, typename U>
SharedPointer<U> ConditionalMapAccess(map<T, SharedPointer<U>> const & Map, T const Key)
{
	auto Iterator = Map.find(Key);

	if (Iterator != Map.end())
		return Iterator->second;

	return nullptr;
}

template <typename T, typename U>
U * ConditionalMapAccess(unordered_map<T, U *> const & Map, T const Key)
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

template <typename T, typename U>
set<T> KeySet(map<T, U> const & Map)
{
	set<T> Return;

	for (auto it : Map)
		Return.insert(it.first);

	return Return;
}

template <typename T>
void AddAtEnd(vector<T> & A, vector<T> const & B)
{
	A.insert(A.end(), B.begin(), B.end());
}

template <typename T>
void EraseRemove(vector<T> & A, T B)
{
	A.erase(std::remove(std::begin(A), std::end(A), B), std::end(A));
}

template <typename T, typename U>
void EraseRemove(vector<T> & A, U B)
{
	A.erase(std::remove(std::begin(A), std::end(A), B), std::end(A));
}

//! \brief Deletes every pointer element of a vector and then clears the vector
template <typename T>
void DeleteAndClear(vector<T> & A)
{
	std::for_each(A.begin(), A.end(), [](T ptr) { delete ptr; });
	A.clear();
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
		std::ifstream FileHandle(FileName);
		std::string String;

		FileHandle.seekg(0, std::ios::end);
		String.reserve((uint) FileHandle.tellg());
		FileHandle.seekg(0, std::ios::beg);

		String.assign((std::istreambuf_iterator<char>(FileHandle)), std::istreambuf_iterator<char>());

		return String;
	}

	static string StripExtension(string const & Path)
	{
		return Path.substr(0, Path.find_last_of("."));
	}

	static string GetExtension(string const & Path)
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
};

class String
{

public:

	static vector<string> SeparateLines(string const & str)
	{
		vector<string> Lines;
		istringstream Stream(str);
		string Line;

		while (getline(Stream, Line))
		{
			Lines.push_back(move(Line));
		}

		return Lines;
	}

	static vector<string> Explode(string const & str, char delimiter)
	{
		vector<string> Words;
		istringstream Stream(str);
		string Word;

		while (getline(Stream, Word, delimiter))
		{
			Words.push_back(move(Word));
		}

		return Words;
	}

	static bool BeginsWith(string const & s, string const & prefix, string & remainder)
	{
		if (s.size() < prefix.size())
		{
			return false;
		}

		if (s.substr(0, prefix.size()) == prefix)
		{
			remainder = s.substr(prefix.size());
			return true;
		}

		return false;
	}

	template <typename... Args>
	static string Build(char const * const Format, Args const &... args)
	{
		return tfm::format(Format, args...);
	}

};
