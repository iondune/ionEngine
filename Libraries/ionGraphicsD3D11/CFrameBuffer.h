
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CRenderTarget.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CFrameBuffer : public IFrameBuffer, public CRenderTarget
			{
			public:

				CFrameBuffer(ID3D11Device * Device);
				~CFrameBuffer();

				void AttachColorTexture(SharedPointer<ITexture2D> Texture, uint const Attachment);
				void AttachDepthTexture(SharedPointer<ITexture2D> Texture);
				void AttachDepthBuffer(SharedPointer<IDepthBuffer> DepthBuffer);

				bool CheckCorrectness();

#pragma warning(suppress: 4250)
			};

		}
	}
}
