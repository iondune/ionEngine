
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			int GetValueTypeOpenGLEnum(EValueType const ValueType);

		bool OpenGLError();
		string GetOpenGLError();
		void PrintOpenGLErrors();
		void PrintOpenGLErrors(c8 const * const Function, c8 const * const File, s32 const Line);

#ifdef _DEBUG
		#define CheckedGLCall(x) do { ion::Graphics::GL::PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__); (x); ion::Graphics::GL::PrintOpenGLErrors(#x, __FILE__, __LINE__); } while (0)
		#define CheckExistingErrors(x) ion::Graphics::GL::PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__);
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

		enum class EPrimitiveType
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
			static u64 const SizeMatrix[7];
			static u32 const PrimitiveMatrix[4];
			static uint const PrimitiveVertices[4];

			static string const TypeStringMatrix[7];
			static string const SizeStringMatrix[7];
			static string const PrimitiveStringMatrix[4];
		};
	}
	}
}
