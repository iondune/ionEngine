

#pragma warning(push)
#pragma warning(disable: 4996)
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#pragma warning(pop)

#include <ionConfig.h>


#ifdef ION_CONFIG_WINDOWS

#include <Windows.h>


class DebugOutBuffer : public std::stringbuf
{

public:

	virtual int sync()
	{
		OutputDebugString(str().c_str());
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
