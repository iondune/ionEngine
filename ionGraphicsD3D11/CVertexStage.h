
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "CShaderStage.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CVertexStage : public IVertexStage, public CShaderStage
			{

			public:

				CVertexStage(ID3D11Device * Device, string const & Source);
				~CVertexStage();

				ID3D11VertexShader * VertexShader = nullptr;
				ID3D11ShaderReflection * Reflector = nullptr;

			};

		}
	}
}
