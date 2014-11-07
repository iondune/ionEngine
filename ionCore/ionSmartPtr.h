
#pragma once

#include "ionConfig.h"

#include <memory>


#ifdef _ION_CONFIG_CPP11_SUPPORT_

template <typename T>
using uniquePtr = std::unique_ptr<T>;
template <typename T>
using sharedPtr = std::shared_ptr<T>;
template <typename T>
using weakPtr = std::weak_ptr<T>;

#else

#define uniquePtr std::unique_ptr
#define sharedPtr std::shared_ptr
#define weakPtr std::weak_ptr

#endif

template <typename T>
static sharedPtr<T> sharedNew(T * const t)
{
	return sharedPtr<T>(t);
}
