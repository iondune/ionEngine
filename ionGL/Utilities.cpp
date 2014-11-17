
#include "Utilities.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		static GLenum LastError = GL_NO_ERROR;

		bool OpenGLError()
		{
			return (LastError = glGetError()) != GL_NO_ERROR;
		}

		string GetOpenGLError()
		{
			string Error = (c8 const *) gluErrorString(LastError);
			LastError = GL_NO_ERROR;

			return Error;
		}

		void PrintOpenGLErrors()
		{
			bool Succeeded = true;

			GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
			{
				c8 const * ErrorString = (c8 const *) gluErrorString(Error);
				Log::Error("OpenGL Error: '%s'", (ErrorString ? ErrorString : ""));
			}
		}

		void PrintOpenGLErrors(c8 const * const Function, c8 const * const File, s32 const Line)
		{
			bool Succeeded = true;

			GLenum Error = glGetError();
			if (Error != GL_NO_ERROR)
			{
				c8 const * ErrorString = (c8 const *) gluErrorString(Error);
				if (ErrorString)
					Log::Error("OpenGL Error in %s at line %d calling function %s: '%s'", File, Line, Function, ErrorString);
				else
					Log::Error("OpenGL Error in %s at line %d calling function %s: '%d 0x%X'", File, Line, Function, Error, Error);
			}
		}

		u32 const Util::TypeMatrix[7] =
		{
			GL_UNSIGNED_BYTE,
			GL_UNSIGNED_SHORT,
			GL_UNSIGNED_INT,
			GL_BYTE,
			GL_SHORT,
			GL_INT,
			GL_FLOAT
		};

		u64 const Util::SizeMatrix[7] =
		{
			sizeof(u8),
			sizeof(u16),
			sizeof(u32),
			sizeof(c8),
			sizeof(s16),
			sizeof(s32),
			sizeof(f32)
		};

		u32 const Util::PrimitiveMatrix[4] =
		{
			GL_POINTS,
			GL_LINES,
			GL_TRIANGLES,
			GL_QUADS
		};
		
		uint const Util::PrimitiveVertices[4] =
		{
			1,
			2,
			3,
			4
		};

		string const Util::TypeStringMatrix[7] =
		{
			"GL_UNSIGNED_BYTE",
			"GL_UNSIGNED_SHORT",
			"GL_UNSIGNED_INT",
			"GL_BYTE",
			"GL_SHORT",
			"GL_INT",
			"GL_FLOAT"
		};

		string const Util::SizeStringMatrix[7] =
		{
			"sizeof(u8)",
			"sizeof(u16)",
			"sizeof(u32)",
			"sizeof(c8)",
			"sizeof(s16)",
			"sizeof(s32)",
			"sizeof(f32)"
		};

		string const Util::PrimitiveStringMatrix[4] =
		{
			"GL_POINTS",
			"GL_LINES",
			"GL_TRIANGLES",
			"GL_QUADS"
		};
	}
}
