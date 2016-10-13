
#include "CFrameBuffer.h"
#include <glad/glad.h>

#include "CTexture.h"
#include "CDepthBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			CFrameBuffer::CFrameBuffer(CWindow * Window)
				: CRenderTarget(Window)
			{
				CheckedGLCall(glGenFramebuffers(1, & Handle));
			}

			CFrameBuffer::~CFrameBuffer()
			{
				if (Handle)
				{
					CheckedGLCall(glDeleteFramebuffers(1, & Handle));
				}
			}

			void CFrameBuffer::AttachColorTexture(SharedPointer<ITexture2D> Texture, uint const Attachment)
			{
				Bind();
				SharedPointer<CTexture2D> GLTexture = std::dynamic_pointer_cast<CTexture2D>(Texture);
				Size = GLTexture->TextureSize;
				CheckedGLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + Attachment, GL_TEXTURE_2D, GLTexture->Handle, 0));

				vector<uint> Attachments;
				for (uint i = 0; i <= Attachment; ++ i)
				{
					Attachments.push_back(GL_COLOR_ATTACHMENT0 + i);
				}
				CheckedGLCall(glDrawBuffers(Attachment + 1, Attachments.data()));
			}

			void CFrameBuffer::AttachDepthTexture(SharedPointer<ITexture2D> Texture)
			{
				Bind();
				CheckedGLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, std::dynamic_pointer_cast<CTexture>(Texture)->Handle, 0));
			}

			void CFrameBuffer::AttachDepthBuffer(SharedPointer<IDepthBuffer> DepthBuffer)
			{
				Bind();
				CheckedGLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, std::dynamic_pointer_cast<CDepthBuffer>(DepthBuffer)->Handle));
			}

			bool CFrameBuffer::CheckCorrectness()
			{
				Bind();
				CheckExistingErrors(glCheckFramebufferStatus);
				uint Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
				if (OpenGLError())
					cerr << "Error occured during glCheckFramebufferStatus: " << GetOpenGLError() << endl;

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

			void CFrameBuffer::Bind()
			{
				if (CurrentlyBound != this)
				{
					CheckedGLCall(glBindFramebuffer(GL_FRAMEBUFFER, Handle));
					if (SpecifiedViewport)
					{
						CheckedGLCall(glViewport(0, 0, Size.X, Size.Y));
					}
					else
					{
						CheckedGLCall(glViewport(ViewportMin.X, ViewportMin.Y, ViewportMax.X, ViewportMax.Y));
					}
					CurrentlyBound = this;
				}
			}

		}
	}
}
