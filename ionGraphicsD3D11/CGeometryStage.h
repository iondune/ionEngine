
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

				static CGeometryStage * Compile(ID3D11Device * Device, string const & Source, string const & SourceName, vector<string> const & IncludeDirectories);
				~CGeometryStage();

				ID3D11GeometryShader * GeometryShader = nullptr;
				ID3D11ShaderReflection * Reflector = nullptr;
				ID3DBlob * CompileBlob = nullptr;

			protected:

				CGeometryStage() = default;

			};

		}
	}
}
