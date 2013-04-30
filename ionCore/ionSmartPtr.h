#ifndef _ION_CORE_IONSMARTPTR_H_INCLUDED_
#define _ION_CORE_IONSMARTPTR_H_INCLUDED_

#include "ionConfig.h"

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>


#ifdef _ION_CONFIG_CPP11_SUPPORT_

template <typename T>
using smartPtr = boost::shared_ptr<T>;
template <typename T>
using smartArray = boost::shared_array<T>;

template <typename T>
using scopedPtr = boost::scoped_ptr<T>;
template <typename T>
using scopedArray = boost::scoped_array<T>;

#else

#define smartPtr boost::shared_ptr
#define smartArray boost::shared_array
#define scopedPtr boost::scoped_ptr
#define scopedArray boost::scoped_array

#endif

template <typename T>
static smartPtr<T> smartNew(T * t)
{
	return smartPtr<T>(t);
}

#endif
