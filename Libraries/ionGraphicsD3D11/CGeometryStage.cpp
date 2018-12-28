
#include "CGeometryStage.h"
#include "Utilities.h"

#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CGeometryStage * CGeometryStage::Compile(ID3D11Device * Device, string const & Source, string const & SourceName, vector<string> const & IncludeDirectories)
			{
				CGeometryStage * Stage = nullptr;

				if (ID3DBlob * ShaderBlob = CompileShaderBlob(Source, EShaderType::Geometry, SourceName, IncludeDirectories))
				{
					Stage = new CGeometryStage();
					CheckedDXCall( Device->CreateGeometryShader(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), nullptr, & Stage->GeometryShader) );
					CheckedDXCall( D3DReflect(ShaderBlob->GetBufferPointer(), ShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) & Stage->Reflector) );
					Stage->CompileBlob = ShaderBlob;
				}

				return Stage;
			}

			CGeometryStage::~CGeometryStage()
			{
				Reflector->Release();
				GeometryShader->Release();
			}

		}
	}
}
