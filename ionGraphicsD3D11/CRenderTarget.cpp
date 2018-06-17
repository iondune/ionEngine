
#include "CRenderTarget.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CRenderTarget::CRenderTarget(ID3D11Device * Device, IDXGISwapChain * SwapChain, CWindow * Window)
			{
				this->Device = Device;
				this->Window = Window;
				Device->GetImmediateContext(& ImmediateContext);

				ID3D11Texture2D * RenderTexture = nullptr;
				CheckedDXCall( SwapChain->GetBuffer(0, IID_PPV_ARGS(&RenderTexture)) );
				CheckedDXCall( Device->CreateRenderTargetView(RenderTexture, nullptr, &RenderTargetView) );
				RenderTexture->Release();

				ID3D11Texture2D * DepthStencilTexture = nullptr;
				D3D11_TEXTURE2D_DESC DepthDesc = {};
				DepthDesc.Width = Window->GetSize().X;
				DepthDesc.Height = Window->GetSize().Y;
				DepthDesc.MipLevels = 1;
				DepthDesc.ArraySize = 1;
				DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				DepthDesc.SampleDesc.Count = 1;
				DepthDesc.SampleDesc.Quality = 0;
				DepthDesc.Usage = D3D11_USAGE_DEFAULT;
				DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				CheckedDXCall( Device->CreateTexture2D(&DepthDesc, nullptr, &DepthStencilTexture) );

				D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
				DSVDesc.Format = DepthDesc.Format;
				DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				CheckedDXCall( Device->CreateDepthStencilView(DepthStencilTexture, &DSVDesc, &DepthStencilView) );
				DepthStencilTexture->Release();
			}

			void CRenderTarget::ClearColor()
			{
				float ClearColor[4];
				ClearColor[0] = Color.Red;
				ClearColor[1] = Color.Green;
				ClearColor[2] = Color.Blue;
				ClearColor[3] = Color.Alpha;
				ImmediateContext->ClearRenderTargetView(RenderTargetView, ClearColor);
			}

			void CRenderTarget::ClearDepth()
			{
				ImmediateContext->ClearDepthStencilView(DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
			}

			void CRenderTarget::ClearColorAndDepth()
			{
				ClearColor();
				ClearDepth();
			}

			void CRenderTarget::SetClearColor(color4f const & Color)
			{
				this->Color = Color;
			}

			CImage * CRenderTarget::ReadImage()
			{
				int const Width = Window->GetSize().X;
				int const Height = Window->GetSize().Y;
				int const BytesPerPixel = 4;

				byte * buffer = new byte[Width * Height * BytesPerPixel]();


				CImage * Image = new CImage(buffer, Window->GetSize(), BytesPerPixel);
				Image->FlipY();
				return Image;
			}

			void CRenderTarget::Bind()
			{
				if (CurrentlyBound != this)
				{
					ImmediateContext->OMSetRenderTargets(1, & RenderTargetView, DepthStencilView);

					D3D11_VIEWPORT Viewport = {};
					Viewport.Width = (FLOAT) Window->GetSize().X;
					Viewport.Height = (FLOAT) Window->GetSize().Y;
					Viewport.MinDepth = 0.0f;
					Viewport.MaxDepth = 1.0f;
					ImmediateContext->RSSetViewports(1, &Viewport);

					CurrentlyBound = this;
				}
			}

			IRenderTarget * CRenderTarget::GetCurrentlyBound()
			{
				return CurrentlyBound;
			}

			void CRenderTarget::SetViewport(vec2i const & Min, vec2i const & Max)
			{
				ViewportMin = Min;
				ViewportMax = Max;
				SpecifiedViewport = true;
			}

			void CRenderTarget::ClearViewport()
			{
				SpecifiedViewport = false;
			}

			CRenderTarget * CRenderTarget::CurrentlyBound = nullptr;;

		}
	}
}
