
#pragma once

#include <thread>
#include <mutex>


using std::thread;
using std::mutex;
typedef std::lock_guard<std::mutex> scopedLock;
