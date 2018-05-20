
#include "Utilities.h"

#include <locale>
#include <codecvt>
#include <string>
#include <comdef.h>


// https://stackoverflow.com/a/3999597/1390945
// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr)
{
	if( wstr.empty() ) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int) wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo( size_needed, 0 );
	WideCharToMultiByte                  (CP_UTF8, 0, wstr.data(), (int) wstr.size(), strTo.data(), size_needed, NULL, NULL);
	return strTo;
}

namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			void PrintHRESULT(int const hr, char const * const Function, char const * const File, int const Line)
			{
				_com_error const err(hr, nullptr);
				string const ErrorString = utf8_encode(err.ErrorMessage());

				if (hr != S_OK)
				{
					Log::Error("DirectX error in file '%s' at line %d calling function '%s': '%s' '%d 0x%X'", File, Line, Function, ErrorString, hr, hr);
				}
			}

		}
	}
}
