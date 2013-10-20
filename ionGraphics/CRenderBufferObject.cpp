#include "CRenderBufferObject.h"

CRenderBufferObject::CRenderBufferObject(GLenum const Format, vec2u const & Size)
{
	glGenRenderbuffers(1, & Handle);
	glBindRenderbuffer(GL_RENDERBUFFER, Handle);
	glRenderbufferStorage(GL_RENDERBUFFER, Format, Size.X, Size.Y);
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

ERenderTargetType const CRenderBufferObject::getRenderTargetType()
{
	return ERenderTargetType::RenderBuffer;
}
