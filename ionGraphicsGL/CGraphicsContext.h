
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderProgram.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include <glad/glad.h>

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
				GLenum GetDrawType(EDrawMode mode);
				void InternalDrawSetup(SharedPointer<IPipelineState> State);
				void InternalDrawTeardown(SharedPointer<IPipelineState> State);

			};

		}
	}
}
