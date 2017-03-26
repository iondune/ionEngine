
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionFramework.h>

#include "ITexture.h"


namespace ion
{
	namespace Graphics
	{

		class IRenderTarget
		{

		public:

			virtual void ClearColor() = 0;
			virtual void ClearDepth() = 0;
			virtual void ClearColorAndDepth() = 0;

			virtual void SetClearColor(color4f const & Color) = 0;

			virtual void Bind() = 0;
			virtual IRenderTarget * GetCurrentlyBound() = 0;
			virtual void SetViewport(vec2i const & Min, vec2i const & Max) = 0;
			virtual void ClearViewport() = 0;

			virtual CImage * ReadImage() = 0;

			virtual ~IRenderTarget()
			{}

		};

		class IDepthBuffer
		{

		public:

			virtual ~IDepthBuffer()
			{}

		};
		
		class IFrameBuffer : public virtual IRenderTarget
		{

		public:

			virtual void AttachColorTexture(SharedPointer<ITexture2D> Texture, uint const Attachment) = 0;
			virtual void AttachDepthTexture(SharedPointer<ITexture2D> Texture) = 0;
			virtual void AttachDepthBuffer(SharedPointer<IDepthBuffer> DepthBuffer) = 0;

			virtual bool CheckCorrectness() = 0;

			virtual ~IFrameBuffer()
			{}

		};

	}
}
