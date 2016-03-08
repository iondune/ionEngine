
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

			virtual SharedPtr<IRenderTarget> GetBackBuffer() = 0;
			virtual SharedPtr<IPipelineState> CreatePipelineState() = 0;

			virtual void Draw(SharedPtr<IPipelineState> State) = 0;
			virtual void DrawInstanced(SharedPtr<IPipelineState> State, uint const InstanceCount) = 0;

		};

	}
}
