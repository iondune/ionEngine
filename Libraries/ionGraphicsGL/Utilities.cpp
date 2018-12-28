
#include "Utilities.h"
#include <glad/glad.h>


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			int GetValueTypeOpenGLEnum(EValueType const ValueType)
			{
				switch (ValueType)
				{
				case EValueType::Float:
					return GL_FLOAT;
				case EValueType::Double:
					return GL_DOUBLE;
				case EValueType::SignedInt8:
					return GL_BYTE;
				case EValueType::SignedInt16:
					return GL_SHORT;
				case EValueType::SignedInt32:
					return GL_INT;
				case EValueType::UnsignedInt8:
					return GL_UNSIGNED_BYTE;
				case EValueType::UnsignedInt16:
					return GL_UNSIGNED_SHORT;
				case EValueType::UnsignedInt32:
					return GL_UNSIGNED_INT;
				default:
					return 0;
				}
			}

			int GetAttributeTypeOpenGLEnum(EAttributeType const AttributeType)
			{
				switch (AttributeType)
				{
				case EAttributeType::Float:
					return GL_FLOAT;
				case EAttributeType::Double:
					return GL_DOUBLE;
				case EAttributeType::Int:
					return GL_INT;
				case EAttributeType::UnsignedInt:
					return GL_UNSIGNED_INT;
				default:
					return 0;
				}
			}

			static GLenum LastError = GL_NO_ERROR;

			bool OpenGLError()
			{
				return (LastError = glGetError()) != GL_NO_ERROR;
			}

			void IgnoreOpenGLError()
			{
				glGetError();
			}

			char const * glErrorString(GLenum const Error)
			{
				switch (Error)
				{
				case GL_NO_ERROR:
					return "GL_NO_ERROR";
				case GL_INVALID_ENUM:
					return "GL_INVALID_ENUM";
				case GL_INVALID_VALUE:
					return "GL_INVALID_VALUE";
				case GL_INVALID_OPERATION:
					return "GL_INVALID_OPERATION";
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					return "GL_INVALID_FRAMEBUFFER_OPERATION";
				case GL_OUT_OF_MEMORY:
					return "GL_OUT_OF_MEMORY";
				case GL_STACK_UNDERFLOW:
					return "GL_STACK_UNDERFLOW";
				case GL_STACK_OVERFLOW:
					return "GL_STACK_OVERFLOW";
				default:
					return "UNKNOWN";
				}
			}

			string GetOpenGLError()
			{
				string Error = glErrorString(LastError);
				LastError = GL_NO_ERROR;
				return Error;
			}

			void PrintOpenGLErrors(char const * const Before)
			{
				bool Succeeded = true;

				if (glGetError)
				{
					GLenum Error = glGetError();
					if (Error != GL_NO_ERROR)
					{
						char const * const ErrorString = glErrorString(Error);
						if (Before)
						{
							Log::Error("OpenGL error before '%s': '%s'", Before, ErrorString);
						}
						else
						{
							Log::Error("OpenGL error: '%s'", ErrorString);
						}
					}
				}
			}

			void PrintOpenGLErrors(char const * const Function, char const * const File, int const Line)
			{
				bool Succeeded = true;

				if (glGetError)
				{
					GLenum Error = glGetError();
					if (Error != GL_NO_ERROR)
					{
						char const * const ErrorString = glErrorString(Error);
						Log::Error("OpenGL error in file '%s' at line %d calling function '%s': '%s' '%d 0x%X'", File, Line, Function, ErrorString, Error, Error);
					}
				}
			}

			bool CheckGLFunctionPointer(void * Ptr, char const * const FunctionName)
			{
				if (nullptr == Ptr)
				{
					Log::Error("OpenGL function is not loaded, must not be supported in current context: %s", FunctionName);
					return false;
				}

				return true;
			}

			uint const Util::ScalarTypeMatrix[9] =
			{
				// Error = 0,
				// Float = 1,
				// Double = 2,
				// SignedInt8 = 3,
				// SignedInt16 = 4,
				// SignedInt32 = 5,
				// UnsignedInt8 = 6,
				// UnsignedInt16 = 7,
				// UnsignedInt32 = 8,

				GL_FALSE,
				GL_FLOAT,
				GL_DOUBLE,
				GL_BYTE,
				GL_SHORT,
				GL_INT,
				GL_UNSIGNED_BYTE,
				GL_UNSIGNED_SHORT,
				GL_UNSIGNED_INT,
			};

			string const Util::ScalarTypeStringMatrix[9] =
			{
				"GL_FALSE",
				"GL_FLOAT",
				"GL_DOUBLE",
				"GL_BYTE",
				"GL_SHORT",
				"GL_INT",
				"GL_UNSIGNED_BYTE",
				"GL_UNSIGNED_SHORT",
				"GL_UNSIGNED_INT",
			};

		}
	}
}
