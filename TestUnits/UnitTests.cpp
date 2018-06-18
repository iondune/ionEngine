
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ionConfig.h>


#ifdef ION_CONFIG_WINDOWS

#include <Windows.h>


class DebugOutBuffer : public std::stringbuf
{

public:

	virtual int sync()
	{
		char const * message = str().c_str();
		int wcharsCount =  MultiByteToWideChar(CP_UTF8, 0, message, -1, NULL, 0);
		wchar_t * wstr = new wchar_t[wcharsCount];
		MultiByteToWideChar                   (CP_UTF8, 0, message, -1, wstr, wcharsCount);
		OutputDebugString(wstr);
		delete[] wstr;

		str("");
		return 0;
	}

};

namespace Catch
{
	std::ostream buffer(new DebugOutBuffer());

	std::ostream & cout()
	{
		return buffer;
	}

	std::ostream & cerr()
	{
		return buffer;
	}

	std::ostream & clog()
	{
		return buffer;
	}

}

#endif
