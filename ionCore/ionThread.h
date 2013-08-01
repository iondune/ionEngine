#pragma once

#include <thread>
#include <mutex>

typedef std::thread thread;
typedef std::mutex mutex;
typedef std::lock_guard<std::mutex> scopedLock;
