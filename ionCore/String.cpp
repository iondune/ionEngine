
#include "String.h"


namespace ion
{

	vector<string> String::SeparateLines(string const & str)
	{
		vector<string> Lines;
		std::istringstream Stream(str);
		string Line;

		while (std::getline(Stream, Line))
		{
			Lines.push_back(move(Line));
		}

		return Lines;
	}

	vector<string> String::Explode(string const & str, char delimiter)
	{
		vector<string> Words;
		std::istringstream Stream(str);
		string Word;

		while (std::getline(Stream, Word, delimiter))
		{
			Words.push_back(move(Word));
		}

		return Words;
	}

	bool String::BeginsWith(string const & s, string const & prefix, string & remainder)
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

}
