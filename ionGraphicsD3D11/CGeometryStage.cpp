
#include "CGeometryStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CGeometryStage::CGeometryStage(ID3D11Device * Device, string const & Source)
			{
				ID3DBlob * ShaderBlob = CompileShaderBlob(Source, EShaderType::Geometry);

				if (ShaderBlob)
				{
					CheckedDXCall( Device->CreateGeometryShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &GeometryShader) );
					CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &Reflector) );
					ShaderBlob->Release();
				}
			}

			CGeometryStage::~CGeometryStage()
			{
				Reflector->Release();
				GeometryShader->Release();
			}

		}
	}
}
