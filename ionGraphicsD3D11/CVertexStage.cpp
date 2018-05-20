
#include "CVertexStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CVertexStage::CVertexStage(ID3D11Device * Device, string const & Source)
			{
				ID3DBlob * ShaderBlob = CompileShaderBlob(Source, "vertex");
				CheckedDXCall( Device->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, &VertexShader) );
				CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &Reflector) );
				ShaderBlob->Release();
			}

			CVertexStage::~CVertexStage()
			{
				Reflector->Release();
				VertexShader->Release();
			}

		}
	}
}
