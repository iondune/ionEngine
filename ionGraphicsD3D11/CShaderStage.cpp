
#include "CShaderStage.h"
#include "Utilities.h"

#include <D3D11.h>
#include <DXGI.h>
#include <D3DCompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			ID3DBlob * ion::Graphics::D3D11::CShaderStage::CompileShaderBlob(string const & Source, string const & EntryPoint)
			{
				UINT CompileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
			#ifdef ION_CONFIG_DEBUG
				CompileFlags |= D3DCOMPILE_DEBUG;
			#endif

				LPCSTR const Profile = "cs_5_0";

				D3D_SHADER_MACRO const defines[] =
				{
					NULL, NULL
				};

				ID3DBlob * ShaderBlob = nullptr;
				ID3DBlob * ErrorBlob = nullptr;

				CheckedDXCall( D3DCompile(
					Source.c_str(), Source.length(),
					NULL, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
					EntryPoint.c_str(), Profile,
					CompileFlags, 0, &ShaderBlob, &ErrorBlob) );

				if (ErrorBlob)
				{
					char * MessageData = new char[ErrorBlob->GetBufferSize() + 1]();
					std::memcpy(MessageData, ErrorBlob->GetBufferPointer(), ErrorBlob->GetBufferSize());
					Log::Error("%s", MessageData);
					ErrorBlob->Release();
				}

				return ShaderBlob;
			}

		}
	}
}
