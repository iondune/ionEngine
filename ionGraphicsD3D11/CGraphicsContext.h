
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShader.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CGraphicsContext : public IGraphicsContext
			{

			public:

				CGraphicsContext(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext, IDXGISwapChain * SwapChain, CWindow * Window);

				SharedPointer<IRenderTarget> GetBackBuffer();

				SharedPointer<IFrameBuffer> CreateFrameBuffer();
				SharedPointer<IPipelineState> CreatePipelineState();

				void Draw(SharedPointer<IPipelineState> State);
				void DrawInstanced(SharedPointer<IPipelineState> State, uint const InstanceCount);

				ID3D11Device * Device = nullptr;
				IDXGISwapChain * SwapChain = nullptr;
				ID3D11DeviceContext * ImmediateContext = nullptr;
				CWindow * Window = nullptr;

			protected:

			};

		}
	}
}
