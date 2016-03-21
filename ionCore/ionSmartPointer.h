
#pragma once

#include "ionConfig.h"

#include <memory>


template <typename T>
using UniquePointer = std::unique_ptr<T>;
template <typename T>
using SharedPointer = std::shared_ptr<T>;
template <typename T>
using WeakPointer = std::weak_ptr<T>;

template <typename T>
static SharedPointer<T> SharedFromNew(T * const t)
{
	return SharedPointer<T>(t);
}

template <typename T, typename... Args>
static SharedPointer<T> MakeShared(Args&&... args)
{
	return std::make_shared<T, Args...>(args...);
}
