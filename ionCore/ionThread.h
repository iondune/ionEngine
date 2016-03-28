
#pragma once

#include <thread>
#include <mutex>
#include <atomic>


using std::thread;
using std::mutex;
typedef std::lock_guard<std::mutex> scopedLock;
