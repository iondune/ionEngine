
#pragma once

////////////////////
// Config Options //
////////////////////

#define _ION_CONFIG_USE_GWEN
#define _ION_CONFIG_GAMEPAD


////////////////////////
// End Config Options //
////////////////////////

#ifdef _ION_CONFIG_GAMEPAD

	#ifdef _WIN32
		#define _ION_CONFIG_WINDOWS_GAMEPAD
	#endif

#endif
