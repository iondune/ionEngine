
#include "Renderbuffer.h"
#include <GL/glew.h>

#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

		Renderbuffer::Renderbuffer(vec2i const & Size)
		{
			CheckedGLCall(glGenRenderbuffers(1, & Handle));
			CheckedGLCall(glBindRenderbuffer(GL_RENDERBUFFER, Handle));
			CheckedGLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Size.X, Size.Y));
			CheckedGLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
		}

		Renderbuffer::~Renderbuffer()
		{
			CheckedGLCall(glDeleteRenderbuffers(1, & Handle));
		}
		}
	}
}
