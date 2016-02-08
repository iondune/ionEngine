
#pragma once

////////////////////
// Config Options //
////////////////////

//#define _ION_CONFIG_SUPPRESS_LOG


////////////////////////
// End Config Options //
////////////////////////


#ifdef _WIN32
	#define ION_CONFIG_WINDOWS
#endif

#ifdef __linux__
	#define ION_CONFIG_LINUX
#endif

#ifdef __APPLE__
	#define ION_CONFIG_OSX
#endif
