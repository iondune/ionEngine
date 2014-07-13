
#pragma once

#include "ionConfig.h"

#include <climits>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <string>
#include <type_traits>
#include <initializer_list>


// 8 bits integer types
#if UCHAR_MAX == 0xFF
    typedef signed   char Int8;
    typedef unsigned char Uint8;
#else
    #error No 8 bits integer type for this platform
#endif

// 16 bits integer types
#if USHRT_MAX == 0xFFFF
    typedef signed   short Int16;
    typedef unsigned short Uint16;
#elif UINT_MAX == 0xFFFF
    typedef signed   int Int16;
    typedef unsigned int Uint16;
#elif ULONG_MAX == 0xFFFF
    typedef signed   long Int16;
    typedef unsigned long Uint16;
#else
    #error No 16 bits integer type for this platform
#endif

// 32 bits integer types
#if USHRT_MAX == 0xFFFFFFFF
    typedef signed   short Int32;
    typedef unsigned short Uint32;
#elif UINT_MAX == 0xFFFFFFFF
    typedef signed   int Int32;
    typedef unsigned int Uint32;
#elif ULONG_MAX == 0xFFFFFFFF
    typedef signed   long Int32;
    typedef unsigned long Uint32;
#else
    #error No 32 bits integer type for this platform
#endif

// 64 bits integer types
#if USHRT_MAX == 0xFFFFFFFFFFFFFFFF
    typedef signed   short Int64;
    typedef unsigned short Uint64;
	#define _ION_64BIT_INTEGERS_DEFINED
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
    typedef signed   int Int64;
    typedef unsigned int Uint64;
	#define _ION_64BIT_INTEGERS_DEFINED
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
    typedef signed   long Int64;
    typedef unsigned long Uint64;
	#define _ION_64BIT_INTEGERS_DEFINED
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
    typedef signed   long long Int64;
    typedef unsigned long long Uint64;
	#define _ION_64BIT_INTEGERS_DEFINED
#endif

// Bit-specified types
typedef Int8   s8;
typedef Uint8  u8;
typedef char   c8;

typedef Int16  s16;
typedef Uint16 u16;

typedef Int32  s32;
typedef Uint32 u32;

typedef float  f32;
typedef double f64;

// Standard types
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned char  byte;

// STL imports
using std::string;
using std::vector;
using std::list;
using std::map;
using std::multimap;
using std::pair;
using std::make_pair;
