
#include "Utilities.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		void PrintOpenGLErrors(c8 const * const Function, c8 const * const File, s32 const Line)
		{
			bool Succeeded = true;

			GLenum Error = glGetError();
			while (Error != GL_NO_ERROR)
			{
				u8 const * ErrorString = gluErrorString(Error);
				std::cerr << "OpenGL Error in " << File << " at line " << Line << " calling function " << Function << ": " << (ErrorString ? ErrorString : "") << std::endl;
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
	}
}
