
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace GL
	{
		void PrintOpenGLErrors(c8 const * const Function, c8 const * const File, s32 const Line);
		#define CheckedGLCall(x) (x); PrintOpenGLErrors(#x, __FILE__, __LINE__);

		enum class EFormatType
		{
			U8 = 0,
			U16 = 1,
			U32 = 2,
			S8 = 3,
			S16 = 4,
			S32 = 5,
			F32 = 6
		};

		class Util
		{
		public:

			static u32 const TypeMatrix[7];
		};
	}
}
