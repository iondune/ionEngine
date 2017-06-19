
/*!
\file ionThread.h
\ingroup ionCore
\brief Brings some standard library thread classes into ion namespace
*/


#pragma once

#include <thread>
#include <mutex>
#include <atomic>


using std::thread;
using std::mutex;

//! \ingroup ionCore
typedef std::lock_guard<std::mutex> scopedLock;

//! \ingroup ionCore
typedef std::lock_guard<std::mutex> LockGuard;
