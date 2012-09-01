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
	if (Attachment >= GL_COLOR_ATTACHMENT0 && Attachment < GL_MAX_COLOR_ATTACHMENTS - GL_COLOR_ATTACHMENT0)
		ColorAttachments[Attachment - GL_COLOR_ATTACHMENT0] = RenderBufferObject;
	else if (Attachment == GL_DEPTH_ATTACHMENT)
		DepthAttachment = RenderBufferObject;

	glBindFramebuffer(GL_FRAMEBUFFER, Handle);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, Attachment, GL_RENDERBUFFER, RenderBufferObject->getHandle());
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CFrameBufferObject::attach(CTexture * Texture, GLenum const Attachment)
{
	if (Attachment >= GL_COLOR_ATTACHMENT0 && Attachment < GL_MAX_COLOR_ATTACHMENTS - GL_COLOR_ATTACHMENT0)
		ColorAttachments[Attachment - GL_COLOR_ATTACHMENT0] = Texture;
	else if (Attachment == GL_DEPTH_ATTACHMENT)
		DepthAttachment = Texture;

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

void CFrameBufferObject::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool const CFrameBufferObject::isValid() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, Handle);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return status == GL_FRAMEBUFFER_COMPLETE;
}

std::map<u32, IRenderTarget *> const & CFrameBufferObject::getColorAttachments()
{
	return ColorAttachments;
}

IRenderTarget const * const CFrameBufferObject::getDepthAttachment()
{
	return DepthAttachment;
}

void bindDeviceBackBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
