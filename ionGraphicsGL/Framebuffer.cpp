
#if 0

#include "Framebuffer.h"
#include <glad/glad.h>

#include "Texture.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
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

		void Framebuffer::Clear(std::vector<EBuffer> Buffers)
		{
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			ion::Graphics::GL::Context::Clear(Buffers);
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}

		u32 Framebuffer::GetHandle() const
		{
			return Handle;
		}

		bool Framebuffer::Check() const
		{
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
			CheckExistingErrors(glCheckFramebufferStatus);
			uint Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (OpenGLError())
				cerr << "Error occured during glCheckFramebufferStatus: " << GetOpenGLError() << endl;
			CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

			if (Status == GL_FRAMEBUFFER_COMPLETE)
				return true;

			string Problem;
			switch (Status)
			{
			case GL_FRAMEBUFFER_UNDEFINED:
				Problem = "Undefined - the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist.";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				Problem = "Incomplete attachment - one or more of the framebuffer attachment points are framebuffer incomplete.";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				Problem = "Incomplete missing attachment - the framebuffer does not have at least one image attached to it.";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				Problem = "Incomplete draw buffer - the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for one or more color attachment point(s) named by GL_DRAW_BUFFERi.";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				Problem = "Incomplete read buffer - GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER.";
				break;

			case GL_FRAMEBUFFER_UNSUPPORTED:
				Problem = "Unsupported - the combination of internal formats of the attached images violates an implementation-dependent set of restrictions.";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				Problem = "Incomplete multisample.";
				break;

			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				Problem = "Incomplete layer targets - one or more framebuffer attachments is layered, and one or more populated attachment is not layered, or all populated color attachments are not from textures of the same target.";
				break;

			default:
				Problem = "Unknown.";
				break;
			}

			cerr << "Problem with framebuffer: " << Problem << endl;
			return false;
		}
		}
	}
}

#endif
