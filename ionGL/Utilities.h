#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>

#include <ionTypes.h>


bool PrintOpenGLErrors(c8 const * const File, s32 const Line)
{
	bool Succeeded = true;

	GLenum Error = glGetError();
	while (Error != GL_NO_ERROR)
	{
		std::cerr << "OpenGL Error in " << File << " at line " << Line << ": " << gluErrorString(Error) << std::endl;
		Succeeded = false;
		Error = glGetError();
	}

	return Succeeded;
}

#define CheckedGLCall(x) (x); PrintOpenGLErrors(__FILE__, __LINE__);
