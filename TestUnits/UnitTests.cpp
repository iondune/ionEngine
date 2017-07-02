
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <ionConfig.h>


#ifdef ION_CONFIG_WINDOWS
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

}
#else
namespace Catch
{
	std::ostream & cout()
	{
		return std::cout;
	}

	std::ostream & cerr()
	{
		return std::cerr;
	}

}
#endif
