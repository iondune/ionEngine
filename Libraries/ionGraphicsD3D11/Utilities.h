
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{
			std::string utf8_encode(const std::wstring &wstr);
			std::wstring utf8_decode(const std::string &str);

			void PrintHRESULT(int const hr, char const * const Function, char const * const File, int const Line);

#ifndef ION_CONFIG_DISABLE_DIAGNOSTICS
			#define CheckedDXCall(x) do { ion::Graphics::D3D11::PrintHRESULT((x), #x, __FILE__, __LINE__); } while (0)
#else
			#define CheckedDXCall(x) (x)
#endif
		}
	}
}
