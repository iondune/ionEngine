
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
using UniquePtr = std::unique_ptr<T>;
template <typename T>
using SharedPtr = std::shared_ptr<T>;
template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename T>
static sharedPtr<T> sharedNew(T * const t)
{
	return sharedPtr<T>(t);
}

template <typename T>
static SharedPtr<T> SharedFromNew(T * const t)
{
	return sharedPtr<T>(t);
}

template <typename T, typename... Args>
static SharedPtr<T> MakeShared(Args&&... args)
{
	return std::make_shared<T, Args...>(args...);
}
