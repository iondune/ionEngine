
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include <D3D11.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CDepthBuffer : public IDepthBuffer
			{
			public:

				CDepthBuffer(ID3D11Device * Device, vec2i const & Size);
				~CDepthBuffer();

				ID3D11Texture2D * DepthStencilTexture = nullptr;
				vec2i TextureSize;

			};

		}
	}
}
