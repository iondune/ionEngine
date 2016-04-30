
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
			int GetAttributeTypeOpenGLEnum(EAttributeType const AttributeType);

			bool OpenGLError();
			void IgnoreOpenGLError();
			string GetOpenGLError();
			void PrintOpenGLErrors(char const * const Before = nullptr);
			void PrintOpenGLErrors(c8 const * const Function, c8 const * const File, s32 const Line);
			bool CheckGLFunctionPointer(void * Ptr, char const * const FunctionName);

#ifdef _DEBUG
			#define CheckedGLCall(x) do { ion::Graphics::GL::PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__); (x); ion::Graphics::GL::PrintOpenGLErrors(#x, __FILE__, __LINE__); } while (0)
			#define CheckExistingErrors(x) ion::Graphics::GL::PrintOpenGLErrors(">>BEFORE<< "#x, __FILE__, __LINE__);
			#define SafeGLCall(FUNCTION, PARAMS)\
				do {\
					ion::Graphics::GL::PrintOpenGLErrors("(somewhere before) "#FUNCTION, __FILE__, __LINE__);\
					if (ion::Graphics::GL::CheckGLFunctionPointer((FUNCTION), #FUNCTION))\
					{\
						FUNCTION PARAMS;\
						ion::Graphics::GL::PrintOpenGLErrors(#FUNCTION, __FILE__, __LINE__);\
					}\
				} while (0);
			#define SafeGLAssignment(LHS, FUNCTION, PARAMS)\
				do {\
					ion::Graphics::GL::PrintOpenGLErrors("(somewhere before) "#FUNCTION, __FILE__, __LINE__);\
					if (ion::Graphics::GL::CheckGLFunctionPointer((FUNCTION), #FUNCTION))\
					{\
						LHS = FUNCTION PARAMS;\
						ion::Graphics::GL::PrintOpenGLErrors(#FUNCTION, __FILE__, __LINE__);\
					}\
				} while (0);
#else
			#define CheckedGLCall(x) (x)
			#define CheckExistingErrors(x)
			#define SafeGLCall(FUNCTION, PARAMS) FUNCTION PARAMS
			#define SafeGLAssignment(LHS, FUNCTION, PARAMS) LHS = FUNCTION PARAMS
#endif

			class Util
			{
			public:

				static u32 const ScalarTypeMatrix[9];
				static u64 const SizeMatrix[7];

				static string const ScalarTypeStringMatrix[9];
				static string const SizeStringMatrix[7];
			};
		}
	}
}
