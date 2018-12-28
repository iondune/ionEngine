
#include "CDepthBuffer.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CDepthBuffer::CDepthBuffer(ID3D11Device * Device, vec2i const & Size)
			{
				TextureSize = Size;

				D3D11_TEXTURE2D_DESC DepthDesc = {};
				DepthDesc.Width = Size.X;
				DepthDesc.Height = Size.Y;
				DepthDesc.MipLevels = 1;
				DepthDesc.ArraySize = 1;
				DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				DepthDesc.SampleDesc.Count = 1;
				DepthDesc.SampleDesc.Quality = 0;
				DepthDesc.Usage = D3D11_USAGE_DEFAULT;
				DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				CheckedDXCall( Device->CreateTexture2D(&DepthDesc, nullptr, &DepthStencilTexture) );
			}

			CDepthBuffer::~CDepthBuffer()
			{
				DepthStencilTexture->Release();
			}

		}
	}
}
