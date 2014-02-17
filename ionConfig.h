
#pragma once

////////////////////
// Config Options //
////////////////////

//#define _ION_CONFIG_CPP11_SUPPORT_
//#define _ION_CONFIG_CUDA_SUPPORT_
//#define _ION_CONFIG_USE_GWEN
//#define _ION_CONFIG_WINDOWS_GAMEPAD

////////////////////////
// End Config Options //
////////////////////////


#ifdef _ION_CONFIG_CUDA_SUPPORT_

	#include <cuda.h>
	#include <cuda_runtime.h>
	// To Do : Add ionCUDA.h include
	#define __universal__ __host__ __device__
	#define ION_FUNC_DEF __universal__

#else

	#define ION_FUNC_DEF

#endif
