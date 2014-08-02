
#include "Framebuffer.h"
#include <GL/glew.h>


namespace ion
{
	namespace GL
	{
		Framebuffer::Framebuffer()
		{
			glGenFramebuffers(1, & Handle);
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, & Handle);
		}
	}
}
