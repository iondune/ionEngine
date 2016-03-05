
#pragma once

#if 0

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Texture.h"
#include "Renderbuffer.h"
#include "Context.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

		struct ForceDefaultFramebuffer
		{};

		class Framebuffer
		{
		public:

			Framebuffer();
			Framebuffer(ForceDefaultFramebuffer);
			~Framebuffer();

			void AttachColorTexture(Texture2D * Texture, u32 const Attachment);
			void AttachDepthTexture(Texture2D * Texture);
			void AttachDepthRenderBuffer(Renderbuffer * RBO);

			Texture2D * GetColorTextureAttachment(u32 const Attachment);
			Texture2D * GetDepthTextureAttachment();

			void Clear(std::vector<EBuffer> Buffers = { EBuffer::Color, EBuffer::Depth });

			u32 GetHandle() const;

			bool Check() const;

		private:

			vector<Texture2D *> ColorAttachments;
			Texture2D * DepthAttachment = nullptr;

			u32 Handle = 0;
		};

		extern Framebuffer * DefaultFrameBuffer;
		}
	}
}

#endif
