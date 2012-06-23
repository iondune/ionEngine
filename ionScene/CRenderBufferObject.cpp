#include "CRenderBufferObject.h"

CRenderBufferObject::CRenderBufferObject(GLenum const Format, SSize2 const & Size)
{
	glGenRenderbuffers(1, & Handle);
	glBindRenderbuffer(GL_RENDERBUFFER, Handle);
	glRenderbufferStorage(GL_RENDERBUFFER, Format, Size.Width, Size.Height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

CRenderBufferObject::~CRenderBufferObject()
{
	glDeleteRenderbuffers(1, & Handle);
}

GLuint const CRenderBufferObject::getHandle()
{
	return Handle;
}
