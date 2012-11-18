#ifndef _IONCORE_IONSMARTPTR_H_INCLUDED_
#define _IONCORE_IONSMARTPTR_H_INCLUDED_

#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp>


template <typename T>
using smartPtr = boost::shared_ptr<T>;
template <typename T>
using smartArray = boost::shared_array<T>;

template <typename T>
using scopedPtr = boost::scoped_ptr<T>;
template <typename T>
using scopedArray = boost::scoped_array<T>;

#endif
