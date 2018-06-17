
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

			class CGeometryStage : public IGeometryStage, public CShaderStage
			{

			public:

				CGeometryStage(ID3D11Device * Device, string const & Source);
				~CGeometryStage();

				ID3D11GeometryShader * GeometryShader = nullptr;
				ID3D11ShaderReflection * Reflector = nullptr;

			};

		}
	}
}
