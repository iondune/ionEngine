
#include "CRenderBufferObject.h"
#include <ionGL.h>


CRenderBufferObject::CRenderBufferObject(GLenum const Format, vec2u const & Size)
{
	CheckedGLCall(glGenRenderbuffers(1, & Handle));
	CheckedGLCall(glBindRenderbuffer(GL_RENDERBUFFER, Handle));
	CheckedGLCall(glRenderbufferStorage(GL_RENDERBUFFER, Format, Size.X, Size.Y));
	CheckedGLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

CRenderBufferObject::~CRenderBufferObject()
{
	CheckedGLCall(glDeleteRenderbuffers(1, & Handle));
}

GLuint const CRenderBufferObject::getHandle()
{
	return Handle;
}

ERenderTargetType const CRenderBufferObject::getRenderTargetType()
{
	return ERenderTargetType::RenderBuffer;
}
