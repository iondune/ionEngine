
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Texture.h"
#include "Renderbuffer.h"


namespace ion
{
	namespace GL
	{
		class Framebuffer
		{
		public:

			Framebuffer();
			~Framebuffer();

			void AttachColorTexture(Texture2D * Texture, u32 const Attachment);
			void AttachDepthTexture(Texture2D * Texture);
			void AttachDepthRenderBuffer(Renderbuffer * RBO);

			Texture2D * GetColorTextureAttachment(u32 const Attachment);
			Texture2D * GetDepthTextureAttachment(u32 const Attachment);

			u32 GetHandle() const;

		private:

			vector<Texture2D *> ColorAttachments;
			Texture2D * DepthAttachment = nullptr;

			u32 Handle;
		};


		extern Framebuffer * DefaultFrameBuffer;
	}
}
