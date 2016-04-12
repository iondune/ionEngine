
#pragma once

#include <ionCore.h>

#include "IPipelineState.h"
#include "IRenderTarget.h"


namespace ion
{
	namespace Graphics
	{

		class IGraphicsContext
		{

		public:

			virtual SharedPointer<IRenderTarget> GetBackBuffer() = 0;

			virtual SharedPointer<IFrameBuffer> CreateFrameBuffer() = 0;
			virtual SharedPointer<IPipelineState> CreatePipelineState() = 0;

			virtual void Draw(SharedPointer<IPipelineState> State) = 0;
			virtual void DrawInstanced(SharedPointer<IPipelineState> State, uint const InstanceCount) = 0;

		};

	}
}
