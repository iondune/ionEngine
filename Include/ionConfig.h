
#pragma once

////////////////////
// Config Options //
////////////////////

//#define ION_CONFIG_SUPPRESS_LOG
//#define ION_CONFIG_DISABLE_DIAGNOSTICS


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

#ifdef ION_CONFIG_WINDOWS
	#ifdef _DEBUG
		#define ION_CONFIG_DEBUG
	#else
		#define ION_CONFIG_RELEASE
	#endif
#else
	#ifdef NDEBUG
		#define ION_CONFIG_RELEASE
	#else
		#define ION_CONFIG_DEBUG
	#endif
#endif
