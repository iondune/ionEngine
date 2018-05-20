
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

				SharedPointer<IRenderTarget> GetBackBuffer();

				SharedPointer<IFrameBuffer> CreateFrameBuffer();
				SharedPointer<IPipelineState> CreatePipelineState();

				void Draw(SharedPointer<IPipelineState> State);
				void DrawInstanced(SharedPointer<IPipelineState> State, uint const InstanceCount);

				CWindow * Window = nullptr;

			protected:

				void InternalBindUniform(uint const Handle, SharedPointer<IUniform const> const Uniform);

				void InternalDrawSetup(SharedPointer<IPipelineState> State);
				void InternalDrawTeardown(SharedPointer<IPipelineState> State);

			};

		}
	}
}
