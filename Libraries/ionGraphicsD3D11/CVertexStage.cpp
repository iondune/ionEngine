
#include "CVertexStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CVertexStage * CVertexStage::Compile(ID3D11Device * Device, string const & Source, string const & SourceName, vector<string> const & IncludeDirectories)
			{
				CVertexStage * Stage = nullptr;

				if (ID3DBlob * ShaderBlob = CompileShaderBlob(Source, EShaderType::Vertex, SourceName, IncludeDirectories))
				{
					Stage = new CVertexStage();
					CheckedDXCall( Device->CreateVertexShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, & Stage->VertexShader) );
					CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) & Stage->Reflector) );
					Stage->CompileBlob = ShaderBlob;
				}

				return Stage;
			}

			CVertexStage::~CVertexStage()
			{
				Reflector->Release();
				VertexShader->Release();
			}

		}
	}
}
