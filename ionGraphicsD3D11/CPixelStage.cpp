
#include "CPixelStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CPixelStage * CPixelStage::Compile(ID3D11Device * Device, string const & Source)
			{
				CPixelStage * Stage = nullptr;

				if (ID3DBlob * ShaderBlob = CompileShaderBlob(Source, EShaderType::Pixel))
				{
					Stage = new CPixelStage();
					CheckedDXCall( Device->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, & Stage->PixelShader) );
					CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) & Stage->Reflector) );
					ShaderBlob->Release();
				}

				return Stage;
			}

			CPixelStage::~CPixelStage()
			{
				Reflector->Release();
				PixelShader->Release();
			}

		}
	}
}
