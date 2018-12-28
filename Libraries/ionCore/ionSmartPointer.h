
/*!
\file ionSmartPointer.h
\ingroup ionCore
\brief Brings some standard library pointer classes into ion namespace
*/


#pragma once

#include "ionTypes.h"

#include <memory>


namespace ion
{

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
	template <typename T, typename... Args>
	static SharedPointer<T> MakeShared(Args&&... args)
	{
		return std::make_shared<T, Args...>(args...);
	}

}
