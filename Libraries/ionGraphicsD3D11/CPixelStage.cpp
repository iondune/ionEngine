
#include "CPixelStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CPixelStage * CPixelStage::Compile(ID3D11Device * Device, string const & Source, string const & SourceName, vector<string> const & IncludeDirectories)
			{
				CPixelStage * Stage = nullptr;

				if (ID3DBlob * ShaderBlob = CompileShaderBlob(Source, EShaderType::Pixel, SourceName, IncludeDirectories))
				{
					Stage = new CPixelStage();
					CheckedDXCall( Device->CreatePixelShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, & Stage->PixelShader) );
					CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) & Stage->Reflector) );
					Stage->CompileBlob = ShaderBlob;
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
