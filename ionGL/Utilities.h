
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace GL
	{
		bool OpenGLError();
		string GetOpenGLError();
		void PrintOpenGLErrors();
		void PrintOpenGLErrors(c8 const * const Function, c8 const * const File, s32 const Line);

#ifdef _DEBUG
		#define CheckedGLCall(x) do { ion::GL::PrintOpenGLErrors("before "#x, __FILE__, __LINE__); (x); ion::GL::PrintOpenGLErrors(#x, __FILE__, __LINE__); } while (0)
		#define CheckExistingErrors(x) ion::GL::PrintOpenGLErrors("before "#x, __FILE__, __LINE__);
#else
		#define CheckedGLCall(x) (x)
		#define CheckExistingErrors(x)
#endif

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

		enum class EPrimativeType
		{
			Points = 0,
			Lines = 1,
			Triangles = 2,
			Quads = 3
		};

		class Util
		{
		public:
			
			static u32 const TypeMatrix[7];
			static u32 const SizeMatrix[7];
			static u32 const PrimativeMatrix[4];

			static string const TypeStringMatrix[7];
			static string const SizeStringMatrix[7];
			static string const PrimativeStringMatrix[4];
		};
	}
}
