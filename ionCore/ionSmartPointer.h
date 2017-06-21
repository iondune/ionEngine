
/*!
\file ionSmartPointer.h
\ingroup ionCore
\brief Brings some standard library pointer classes into ion namespace
*/


#pragma once

#include "ionConfig.h"

#include <memory>


//! \ingroup ionCore
template <typename T>
using UniquePointer = std::unique_ptr<T>;

//! \ingroup ionCore
template <typename T>
using SharedPointer = std::shared_ptr<T>;

//! \ingroup ionCore
template <typename T>
using WeakPointer = std::weak_ptr<T>;

//! \ingroup ionCore
template <typename T>
static SharedPointer<T> SharedFromNew(T * const t)
{
	return SharedPointer<T>(t);
}

//! \ingroup ionCore
template <typename T, typename... Args>
static SharedPointer<T> MakeShared(Args&&... args)
{
	return std::make_shared<T, Args...>(args...);
}
