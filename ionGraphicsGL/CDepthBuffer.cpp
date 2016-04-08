
#include "CDepthBuffer.h"
#include <glad/glad.h>



namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			CDepthBuffer::CDepthBuffer(vec2i const & Size)
			{
				CheckedGLCall(glGenRenderbuffers(1, & Handle));
				CheckedGLCall(glBindRenderbuffer(GL_RENDERBUFFER, Handle));
				CheckedGLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, Size.X, Size.Y));
				CheckedGLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
			}

			CDepthBuffer::~CDepthBuffer()
			{
				CheckedGLCall(glDeleteRenderbuffers(1, & Handle));
			}

		}
	}
}
