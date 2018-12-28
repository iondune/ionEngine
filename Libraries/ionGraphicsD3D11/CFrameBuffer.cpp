
#include "CFrameBuffer.h"

#include "CTexture.h"
#include "CDepthBuffer.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CFrameBuffer::CFrameBuffer(ID3D11Device * Device)
				: CRenderTarget(Device)
			{
			}

			CFrameBuffer::~CFrameBuffer()
			{
			}

			void CFrameBuffer::AttachColorTexture(SharedPointer<ITexture2D> Texture, uint const Attachment)
			{
				SharedPointer<ion::Graphics::D3D11::CTexture2D> D3DTexture = std::dynamic_pointer_cast<ion::Graphics::D3D11::CTexture2D>(Texture);

				if (D3DTexture && D3DTexture->Texture2D)
				{
					ID3D11RenderTargetView * RenderTargetView = nullptr;
					CheckedDXCall( Device->CreateRenderTargetView(D3DTexture->Texture2D, nullptr, &RenderTargetView) );

					if (Attachment >= RenderTargetViews.size())
					{
						RenderTargetViews.resize(Attachment + 1, nullptr);
					}

					RenderTargetViews[Attachment] = RenderTargetView;

					Size.X = Max(Size.X, D3DTexture->TextureSize.X);
					Size.Y = Max(Size.Y, D3DTexture->TextureSize.Y);

					Rebind();
				}
			}

			void CFrameBuffer::AttachDepthTexture(SharedPointer<ITexture2D> Texture)
			{
				SharedPointer<ion::Graphics::D3D11::CTexture2D> D3DTexture = std::dynamic_pointer_cast<ion::Graphics::D3D11::CTexture2D>(Texture);

				if (DepthStencilView)
				{
					DepthStencilView->Release();
					DepthStencilView = nullptr;
				}

				D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
				DSVDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				CheckedDXCall( Device->CreateDepthStencilView(D3DTexture->Texture2D, & DSVDesc, & DepthStencilView) );

				Size.X = Max(Size.X, D3DTexture->TextureSize.X);
				Size.Y = Max(Size.Y, D3DTexture->TextureSize.Y);

				Rebind();
			}

			void CFrameBuffer::AttachDepthBuffer(SharedPointer<IDepthBuffer> DepthBuffer)
			{
				SharedPointer<ion::Graphics::D3D11::CDepthBuffer> D3DTexture = std::dynamic_pointer_cast<ion::Graphics::D3D11::CDepthBuffer>(DepthBuffer);

				if (DepthStencilView)
				{
					DepthStencilView->Release();
					DepthStencilView = nullptr;
				}

				D3D11_DEPTH_STENCIL_VIEW_DESC DSVDesc = {};
				DSVDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				DSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				CheckedDXCall( Device->CreateDepthStencilView(D3DTexture->DepthStencilTexture, & DSVDesc, & DepthStencilView) );

				Size.X = Max(Size.X, D3DTexture->TextureSize.X);
				Size.Y = Max(Size.Y, D3DTexture->TextureSize.Y);

				Rebind();
			}

			bool CFrameBuffer::CheckCorrectness()
			{
				return true;
			}

		}
	}
}
