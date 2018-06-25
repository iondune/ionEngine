
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

			class CShaderIncludeManager : public ID3DInclude
			{

				CShaderIncludeManager(CShaderIncludeManager const &) = delete;
				CShaderIncludeManager & operator = (CShaderIncludeManager const &) = delete;

			public:

				CShaderIncludeManager(vector<string> const & includeDirectories)
					: IncludeDirectories(includeDirectories)
				{

				}

				~CShaderIncludeManager()
				{
					DeleteAndClear(OpenFiles);
				}

				vector<string> IncludeDirectories;

				struct SOpenFile
				{
					string Contents;
				};

				vector<SOpenFile *> OpenFiles;

				HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes)
				{
					for (string AssetPath : IncludeDirectories)
					{
						string const FilePath = AssetPath + pFileName;

						if (File::Exists(FilePath))
						{
							SOpenFile * OpenFile = new SOpenFile();
							OpenFile->Contents = File::ReadAsString(FilePath);
							OpenFiles.push_back(OpenFile);

							*ppData = OpenFile->Contents.c_str();
							*pBytes = OpenFile->Contents.length();
							return S_OK;
						}
					}

					return E_FAIL;
				}

				HRESULT Close(LPCVOID pData)
				{
					return S_OK;
				}
			};

			ID3DBlob * ion::Graphics::D3D11::CShaderStage::CompileShaderBlob(string const & Source, int const ShaderType, string const & SourceName, vector<string> const & IncludeDirectories)
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

				CShaderIncludeManager Include(IncludeDirectories);

				HRESULT result = D3DCompile(
					Source.c_str(), Source.length(),
					SourceName.length() ? SourceName.c_str() : nullptr, defines, & Include,
					EntryPoint, Profile,
					CompileFlags, 0, & ShaderBlob, & ErrorBlob);

				if (result != S_OK)
				{
					Log::Error("Shader failed to compile.");
				}

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
