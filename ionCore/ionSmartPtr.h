
#pragma once

#include "ionConfig.h"

#include <memory>


template <typename T>
using uniquePtr = std::unique_ptr<T>;
template <typename T>
using sharedPtr = std::shared_ptr<T>;
template <typename T>
using weakPtr = std::weak_ptr<T>;

template <typename T>
static sharedPtr<T> sharedNew(T * const t)
{
	return sharedPtr<T>(t);
}
