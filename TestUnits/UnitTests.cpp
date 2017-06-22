
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <ionCore.h>


int main(int argc, char * const argv[])
{
	int result = Catch::Session().run(argc, argv);

#ifdef PAUSE
#ifdef WIN32
	ion::WaitForUser();
#endif
#endif

	return result;
}
