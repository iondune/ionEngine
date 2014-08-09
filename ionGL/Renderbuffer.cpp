
#include "Renderbuffer.h"
#include <GL/glew.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		Renderbuffer::Renderbuffer()
		{
			CheckedGLCall(glGenRenderbuffers(1, & Handle));
		}

		Renderbuffer::~Renderbuffer()
		{
			CheckedGLCall(glDeleteRenderbuffers(1, & Handle));
		}
	}
}
