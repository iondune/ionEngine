
#include "Framebuffer.h"
#include <GL/glew.h>

#include "Texture.h"
#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		Framebuffer * DefaultFrameBuffer = new Framebuffer(ForceDefaultFramebuffer{});


		Framebuffer::Framebuffer()
		{
			CheckedGLCall(glGenFramebuffers(1, & Handle));
		}
		
		Framebuffer::Framebuffer(ForceDefaultFramebuffer f)
		{}

		Framebuffer::~Framebuffer()
		{
			if (Handle)
				CheckedGLCall(glDeleteFramebuffers(1, & Handle));
		}

		void Framebuffer::AttachColorTexture(Texture2D * Texture, u32 const Attachment)
		{
			if (! Handle)
				return;

			if (ColorAttachments.size() <= Attachment)
				ColorAttachments.resize(Attachment + 1, nullptr);

			ColorAttachments[Attachment] = Texture;

			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckedGLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Attachment, GL_TEXTURE_2D, Texture->GetHandle(), 0));
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		void Framebuffer::AttachDepthTexture(Texture2D * Texture)
		{
			if (! Handle)
				return;

			DepthAttachment = Texture;

			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckedGLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Texture->GetHandle(), 0));
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		void Framebuffer::AttachDepthRenderBuffer(Renderbuffer * RBO)
		{
			if (! Handle)
				return;

			DepthAttachment = nullptr;

			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckedGLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO->Handle));
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		Texture2D * Framebuffer::GetColorTextureAttachment(u32 const Attachment)
		{
			if (Attachment >= ColorAttachments.size())
				return nullptr;

			return ColorAttachments[Attachment];
		}

		Texture2D * Framebuffer::GetDepthTextureAttachment()
		{
			return DepthAttachment;
		}
		
		void Framebuffer::Clear(std::initializer_list<EBuffer> Buffers)
		{
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			ion::GL::Context::Clear(Buffers);
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		u32 Framebuffer::GetHandle() const
		{
			return Handle;
		}
	}
}
