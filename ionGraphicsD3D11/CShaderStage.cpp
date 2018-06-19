
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

			ID3DBlob * ion::Graphics::D3D11::CShaderStage::CompileShaderBlob(string const & Source, int const ShaderType)
			{
				UINT CompileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
			#ifdef ION_CONFIG_DEBUG
				CompileFlags |= D3DCOMPILE_DEBUG;
			#endif

				LPCSTR Profile = "none";
				LPCSTR EntryPoint = "none";

				switch (ShaderType)
				{

				case EShaderType::Pixel:
					Profile = "ps_5_0";
					EntryPoint = "pixel";
					break;

				case EShaderType::Vertex:
					Profile = "vs_5_0";
					EntryPoint = "vertex";
					break;

				case EShaderType::Geometry:
					Profile = "gs_5_0";
					EntryPoint = "geometry";
					break;

				}

				D3D_SHADER_MACRO const defines[] =
				{
					NULL, NULL
				};

				ID3DBlob * ShaderBlob = nullptr;
				ID3DBlob * ErrorBlob = nullptr;

				HRESULT result = D3DCompile(
					Source.c_str(), Source.length(),
					NULL, defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
					EntryPoint, Profile,
					CompileFlags, 0, &ShaderBlob, &ErrorBlob);

				if (result != S_OK)
				{
					Log::Error("Shader failed to compile.");
					if (ErrorBlob)
					{
						char * MessageData = new char[ErrorBlob->GetBufferSize() + 1]();
						std::memcpy(MessageData, ErrorBlob->GetBufferPointer(), ErrorBlob->GetBufferSize());
						Log::Error("%s", MessageData);
						ErrorBlob->Release();
					}

					if (ShaderBlob)
					{
						ShaderBlob->Release();
						ShaderBlob = nullptr;
					}
				}

				return ShaderBlob;
			}

		}
	}
}
