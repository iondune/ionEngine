#include "CFrameBufferObject.h"

CFrameBufferObject::CFrameBufferObject()
{
	glGenFramebuffers(1, & Handle);
}

CFrameBufferObject::~CFrameBufferObject()
{
	glDeleteFramebuffers(1, & Handle);
}

void CFrameBufferObject::attachColorTexture(CTexture * Texture, u32 const Attachment)
{
	ColorAttachments[Attachment] = Texture;

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Attachment, GL_TEXTURE_2D, Texture->getTextureHandle(), 0);
	unbind();
}

void CFrameBufferObject::attachDepthTexture(CTexture * Texture)
{
	DepthAttachment = Texture;

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Texture->getTextureHandle(), 0);
	unbind();
}

void CFrameBufferObject::attachDepthRenderBuffer(CRenderBufferObject * RenderBufferObject)
{
	DepthAttachment = RenderBufferObject;

	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RenderBufferObject->getHandle());
	unbind();
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

std::map<u32, CTexture *> const & CFrameBufferObject::getColorAttachments()
{
	return ColorAttachments;
}

IRenderTarget const * const CFrameBufferObject::getDepthAttachment()
{
	return DepthAttachment;
}

void CFrameBufferObject::bindDeviceBackBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
