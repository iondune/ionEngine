
/*!
\file ionTypes.h
\ingroup ionCore
\brief Defines typedefs for integer and floating point types
*/


#pragma once

#include <ionConfig.h>

#include <string>
#include <vector>
#include <array>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <deque>
#include <utility>
#include <initializer_list>

#include <climits>
#include <limits>
#include <cstdint>


namespace ion
{

	using namespace std::string_literals;

	// STL imports
	using std::string;
	using std::vector;
	using std::list;
	using std::set;
	using std::map;
	using std::unordered_map;
	using std::deque;
	using std::pair;

	// Standard types
	typedef unsigned short      ushort;
	typedef unsigned int        uint;
	typedef unsigned long       ulong;
	typedef unsigned long long  ulonglong;
	typedef unsigned char       byte;

	// Specific bit lengths
	typedef   int8_t  int8;
	typedef  uint8_t uint8;
	typedef  int16_t  int16;
	typedef uint16_t uint16;
	typedef  int32_t  int32;
	typedef uint32_t uint32;
	typedef  int64_t  int64;
	typedef uint64_t uint64;

}
