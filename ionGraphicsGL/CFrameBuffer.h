
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"
#include "CRenderTarget.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class CFrameBuffer : public IFrameBuffer, public CRenderTarget
			{
			public:

				CFrameBuffer(CWindow * Window);
				~CFrameBuffer();

				void AttachColorTexture(SharedPointer<ITexture2D> Texture, uint const Attachment);
				void AttachDepthTexture(SharedPointer<ITexture2D> Texture);
				void AttachDepthBuffer(SharedPointer<IDepthBuffer> DepthBuffer);

				bool Check();

				virtual void Bind();

				uint Handle = 0;

#pragma warning(suppress: 4250)
			};

		}
	}
}
