
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderProgram.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class CGraphicsContext : public IGraphicsContext
			{

			public:

				CGraphicsContext(CWindow * Window);

				SharedPtr<IPipelineState> CreatePipelineState();
				SharedPtr<IRenderTarget> GetBackBuffer();

				void Draw(SharedPtr<IPipelineState> State);
				void DrawInstanced(SharedPtr<IPipelineState> State, uint const InstanceCount);

				CWindow * Window = nullptr;

			protected:

				void InternalDrawSetup(SharedPtr<IPipelineState> State);
				void InternalDrawTeardown(SharedPtr<IPipelineState> State);

			};

		}
	}
}
