
#include "CPixelStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CPixelStage::CPixelStage(ID3D11Device * Device, string const & Source)
			{
				ID3DBlob * ShaderBlob = CompileShaderBlob(Source, "pixel");
				CheckedDXCall( Device->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &PixelShader) );
				CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &Reflector) );
				ShaderBlob->Release();
			}

			CPixelStage::~CPixelStage()
			{
				Reflector->Release();
				PixelShader->Release();
			}

		}
	}
}
