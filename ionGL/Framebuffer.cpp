
#include "Framebuffer.h"
#include <GL/glew.h>

#include "Texture.h"
#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		Framebuffer::Framebuffer()
		{
			CheckedGLCall(glGenFramebuffers(1, & Handle));
		}

		Framebuffer::~Framebuffer()
		{
			CheckedGLCall(glDeleteFramebuffers(1, & Handle));
		}

		void Framebuffer::AttachColorTexture(Texture2D * Texture, u32 const Attachment)
		{
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckedGLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Attachment, GL_TEXTURE_2D, Texture->GetHandle(), 0));
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		void Framebuffer::AttachDepthTexture(Texture2D * Texture)
		{
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckedGLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Texture->GetHandle(), 0));
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		void Framebuffer::AttachDepthRenderBuffer(Renderbuffer * RBO)
		{
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckedGLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO->Handle));
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
	}
}
