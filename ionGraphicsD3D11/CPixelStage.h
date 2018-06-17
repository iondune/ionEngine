
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderStage.h"

#include <D3D11.h>
#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CPixelStage : public IPixelStage, public CShaderStage
			{

			public:

				CPixelStage(ID3D11Device * Device, string const & Source);
				~CPixelStage();

				ID3D11PixelShader * PixelShader = nullptr;
				ID3D11ShaderReflection * Reflector = nullptr;

			};

		}
	}
}
