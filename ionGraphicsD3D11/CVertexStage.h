
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

			class CVertexStage : public IVertexStage, public CShaderStage
			{

			public:

				static CVertexStage * Compile(ID3D11Device * Device, string const & Source);
				~CVertexStage();

				ID3D11VertexShader * VertexShader = nullptr;
				ID3D11ShaderReflection * Reflector = nullptr;

			protected:

				CVertexStage() = default;

			};

		}
	}
}
