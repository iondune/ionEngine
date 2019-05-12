
#include "ionOS.h"

#include <Windows.h>


namespace ion
{

	namespace OS
	{

		uint64 GetCurrentFileTime()
		{
			SYSTEMTIME st;
			GetSystemTime(& st);

			FILETIME ft = { 0 };
			int success = SystemTimeToFileTime(& st, & ft);

			uint64 t = ft.dwLowDateTime | static_cast<uint64>(ft.dwHighDateTime) << 32;

			return t;
		}

	}

}
