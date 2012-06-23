#include "CFrameBufferObject.h"

CFrameBufferObject::CFrameBufferObject()
{
	glGenFramebuffers(1, & Handle);
}

CFrameBufferObject::~CFrameBufferObject()
{
	glDeleteFramebuffers(1, & Handle);
}

void CFrameBufferObject::attach(CRenderBufferObject * RenderBufferObject, GLenum const Attachment)
{
	glBindFramebuffer(GL_FRAMEBUFFER, Handle);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, Attachment, GL_RENDERBUFFER, RenderBufferObject->getHandle());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CFrameBufferObject::attach(CTexture * Texture, GLenum const Attachment)
{
	glBindFramebuffer(GL_FRAMEBUFFER, Handle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, Attachment, GL_TEXTURE_2D, Texture->getTextureHandle(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint const CFrameBufferObject::getHandle()
{
	return Handle;
}

void CFrameBufferObject::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Handle);
}

bool const CFrameBufferObject::isValid() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, Handle);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return status == GL_FRAMEBUFFER_COMPLETE;
}
