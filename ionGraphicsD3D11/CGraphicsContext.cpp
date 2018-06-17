
#include "CGraphicsContext.h"

#include "CFrameBuffer.h"
#include "CRenderTarget.h"
#include "CPipelineState.h"
#include "CTexture.h"
#include "CDrawContext.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CGraphicsContext::CGraphicsContext(ID3D11Device * Device, ID3D11DeviceContext * ImmediateContext, IDXGISwapChain * SwapChain, CWindow * Window)
			{
				this->Device = Device;
				this->ImmediateContext = ImmediateContext;
				this->SwapChain = SwapChain;
				this->Window = Window;
			}

			SharedPointer<IRenderTarget> CGraphicsContext::GetBackBuffer()
			{
				return std::make_shared<CRenderTarget>(Device, SwapChain, Window);
			}

			SharedPointer<IFrameBuffer> CGraphicsContext::CreateFrameBuffer()
			{
				return nullptr;// std::make_shared<CFrameBuffer>();
			}

			SharedPointer<IPipelineState> CGraphicsContext::CreatePipelineState()
			{
				return std::make_shared<CPipelineState>(Device, ImmediateContext);
			}

			void CGraphicsContext::Draw(SharedPointer<IPipelineState> State)
			{
				SharedPointer<CPipelineState> PipelineState = std::dynamic_pointer_cast<CPipelineState>(State);
				PipelineState->Draw();
			}

			void CGraphicsContext::DrawInstanced(SharedPointer<IPipelineState> State, uint const InstanceCount)
			{
			}

		}
	}
}
