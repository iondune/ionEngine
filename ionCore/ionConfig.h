#ifndef _IONCORE_CONFIG_H_INCLUDED_
#define _IONCORE_CONFIG_H_INCLUDED_


//#define _ION_CONFIG_CUDA_SUPPORT_

	#ifdef _ION_CONFIG_CUDA_SUPPORT_

		#include <cuda.h>
		#include <cuda_runtime.h>
		// To Do : Add ionCUDA.h include
		#define __universal__ __host__ __device__
		#define ION_FUNC_DEF __universal__

	#else

		#define ION_FUNC_DEF

	#endif

#endif
