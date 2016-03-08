
#include <ionCore.h>


int main()
{
	bool Success = true;

	std::cout <<
		"Config check..." << std::endl <<
		"---------------" << std::endl;
#ifdef ION_CONFIG_WINDOWS
	std::cout << "This is a Windows build." << std::endl;
#else
#ifdef ION_CONFIG_LINUX
	std::cout << "This is a Linux build." << std::endl;
#else
#ifdef ION_CONFIG_OSX
	std::cout << "This is an OS X build." << std::endl;
#else
	std::cout << "Unknown OS configuration." << std::endl;
	Success = false;
#endif
#endif
#endif

#ifdef ION_CONFIG_DEBUG
	std::cout << "This is a Debug build." << std::endl;
#else
#ifdef ION_CONFIG_RELEASE
	std::cout << "This is a Release build." << std::endl;
#else
	std::cout << "Unknown build type configuration." << std::endl;
	Success = false;
#endif
#endif

	return Success ? 0 : 1;
}
