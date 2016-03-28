
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

				SharedPointer<IPipelineState> CreatePipelineState();
				SharedPointer<IRenderTarget> GetBackBuffer();

				void Draw(SharedPointer<IPipelineState> State);
				void DrawInstanced(SharedPointer<IPipelineState> State, uint const InstanceCount);

				CWindow * Window = nullptr;

			protected:

				void InternalDrawSetup(SharedPointer<IPipelineState> State);
				void InternalDrawTeardown(SharedPointer<IPipelineState> State);

			};

		}
	}
}
