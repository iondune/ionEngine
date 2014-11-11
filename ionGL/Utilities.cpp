
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
				std::cerr << "OpenGL Error: " << (ErrorString ? ErrorString : "") << std::endl;
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
					std::cerr << "OpenGL Error in " << File << " at line " << Line << " calling function " << Function << ": '" << ErrorString << "'" << std::endl;
				else
					std::cerr << "OpenGL Error in " << File << " at line " << Line << " calling function " << Function << ": '" << Error << " (0x" << std::hex << Error << ")'" << std::endl;
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

		u32 const Util::PrimativeMatrix[4] =
		{
			GL_POINTS,
			GL_LINES,
			GL_TRIANGLES,
			GL_QUADS
		};
		
		uint const Util::PrimativeVertices[4] =
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

		string const Util::PrimativeStringMatrix[4] =
		{
			"GL_POINTS",
			"GL_LINES",
			"GL_TRIANGLES",
			"GL_QUADS"
		};
	}
}
