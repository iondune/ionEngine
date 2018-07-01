
#include "CVertexBuffer.h"
#include "Utilities.h"

#include <d3dcompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CInputLayout::CInputLayout(ID3D11Device * Device, vector<SInputLayoutElement> const & LayoutElements, bool const Instancing)
			{
				string Source = "";
				Source += "struct VS_INPUT\n";
				Source += "{\n";
				int Count = 0;
				for (SInputLayoutElement const & Element : LayoutElements)
				{
					Source += "    ";
					switch (Element.Type)
					{
					case EAttributeType::Float:
					case EAttributeType::Double:
						Source += "float";
						break;
					case EAttributeType::Int:
						Source += "int";
						break;
					case EAttributeType::UnsignedInt:
						Source += "uint";
						break;
					}

					if (Element.Components > 1)
					{
						Source += std::to_string(Element.Components);
					}

					Source += " field" + std::to_string(Count) + " : " + Element.Name + "0;\n";

					Count ++;
				}

				Source += "};\n";
				Source += "\n";
				Source += "void main(VS_INPUT input) {}\n";
				Source += "\n";

				UINT CompileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef ION_CONFIG_DEBUG
				CompileFlags |= D3DCOMPILE_DEBUG;
#endif

				ID3DBlob * ShaderBlob = nullptr;
				ID3DBlob * ErrorBlob = nullptr;
				CheckedDXCall( D3DCompile(
					Source.c_str(), Source.length(),
					NULL, NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE,
					"main", "vs_5_0",
					CompileFlags, 0, &ShaderBlob, &ErrorBlob) );

				if (ErrorBlob)
				{
					char * MessageData = new char[ErrorBlob->GetBufferSize() + 1]();
					std::memcpy(MessageData, ErrorBlob->GetBufferPointer(), ErrorBlob->GetBufferSize());
					Log::Error("%s", MessageData);
					delete[] MessageData;

					Log::Error("Shader source:");
					Log::Error("---");
					Log::Error("%s", Source);
					Log::Error("---");
					ErrorBlob->Release();
				}

				vector<D3D11_INPUT_ELEMENT_DESC> Layout;

				int ByteAlignment = 0;

				//vector<std::wstring> SemanticNames;

				//for (SInputLayoutElement const & Element : LayoutElements)
				//{
				//	SemanticNames.push_back(utf8_decode(Element.Name));
				//}

				//int i = 0;
				for (SInputLayoutElement const & Element : LayoutElements)
				{
					D3D11_INPUT_ELEMENT_DESC Desc;
					Desc.SemanticName = Element.Name.c_str();// SemanticNames[i++].c_str();
					Desc.SemanticIndex = 0;
					Desc.InputSlot = 0;
					Desc.InputSlotClass = (Instancing ? D3D11_INPUT_PER_INSTANCE_DATA : D3D11_INPUT_PER_VERTEX_DATA);
					Desc.InstanceDataStepRate = 0;
					
					static DXGI_FORMAT const Lookup[4][4] =
					{
						{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
						{ DXGI_FORMAT_R32_SINT,  DXGI_FORMAT_R32G32_SINT,  DXGI_FORMAT_R32G32B32_SINT,  DXGI_FORMAT_R32G32B32A32_SINT  },
						{ DXGI_FORMAT_R32_UINT,  DXGI_FORMAT_R32G32_UINT,  DXGI_FORMAT_R32G32B32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT  },
						{ DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_R32G32_FLOAT, DXGI_FORMAT_R32G32B32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
					};

					if (Element.Type == EAttributeType::Double)
					{
						Log::Warn("InputLayout double types not supported.");
					}

					Desc.Format = Lookup[(int) Element.Type][Element.Components - 1];
					Desc.AlignedByteOffset = ByteAlignment;

					ByteAlignment += 4 * Element.Components;

					Layout.push_back(Desc);
				}

				CheckedDXCall( Device->CreateInputLayout(
					Layout.data(),
					(UINT) Layout.size(),
					ShaderBlob->GetBufferPointer(),
					(unsigned int) ShaderBlob->GetBufferSize(),
					&InputLayout) );
				ShaderBlob->Release();
			}

			CInputLayout::~CInputLayout()
			{
				InputLayout->Release();
			}

			CVertexBuffer::CVertexBuffer(ID3D11Device * Device)
			{
				this->Device = Device;
			}

			CVertexBuffer::~CVertexBuffer()
			{
				VertexBuffer->Release();
			}
			
			void CVertexBuffer::UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements)
			{
				D3D11_BUFFER_DESC VertexBufferDesc = {};
				VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				VertexBufferDesc.ByteWidth = (unsigned int) (DataSize * NumberOfElements);
				VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				if (VertexBufferDesc.ByteWidth)
				{
					D3D11_SUBRESOURCE_DATA InitData = {};
					InitData.pSysMem = Data;
					CheckedDXCall(Device->CreateBuffer(&VertexBufferDesc, &InitData, &VertexBuffer));
				}
			}

			void CVertexBuffer::UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements)
			{
				ID3D11DeviceContext * ImmediateContext = nullptr;
				Device->GetImmediateContext(&ImmediateContext);

				D3D11_BOX Box = {};
				Box.left = (unsigned int) Offset;
				Box.right = (unsigned int) (Offset + DataSize * NumberOfElements);

				ImmediateContext->UpdateSubresource(VertexBuffer, 0, &Box, Data, (unsigned int) (DataSize * NumberOfElements), 0);
			}

			void CVertexBuffer::SetInputLayout(SInputLayoutElement const * const InputLayoutArray, int const NumElements)
			{
				InputLayoutElements.clear();
				InputLayoutElements.insert(InputLayoutElements.begin(), InputLayoutArray, InputLayoutArray + NumElements);

				LayoutSize = 0;

				for (SInputLayoutElement const & Element : InputLayoutElements)
				{
					switch (Element.Type)
					{
					case EAttributeType::Double:
						LayoutSize += 8 * Element.Components;
						break;
					case EAttributeType::Float:
					case EAttributeType::Int:
					case EAttributeType::UnsignedInt:
						LayoutSize += 4 * Element.Components;
						break;
					}
				}
			}

			CInstanceBuffer::CInstanceBuffer(ID3D11Device * Device)
			{
				this->Device = Device;
			}

			CInstanceBuffer::~CInstanceBuffer()
			{
				Buffer->Release();
			}

			void CInstanceBuffer::UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements)
			{
				D3D11_BUFFER_DESC VertexBufferDesc = {};
				VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				VertexBufferDesc.ByteWidth = (unsigned int) (DataSize * NumberOfElements);
				VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				if (VertexBufferDesc.ByteWidth)
				{
					D3D11_SUBRESOURCE_DATA InitData = {};
					InitData.pSysMem = Data;
					CheckedDXCall(Device->CreateBuffer(&VertexBufferDesc, &InitData, & Buffer));
				}
			}

			void CInstanceBuffer::UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements)
			{
				ID3D11DeviceContext * ImmediateContext = nullptr;
				Device->GetImmediateContext(&ImmediateContext);

				D3D11_BOX Box = {};
				Box.left = (unsigned int) Offset;
				Box.right = (unsigned int) (Offset + DataSize * NumberOfElements);

				ImmediateContext->UpdateSubresource(Buffer, 0, &Box, Data, (unsigned int) (DataSize * NumberOfElements), 0);
			}

			void CInstanceBuffer::SetInputLayout(SInputLayoutElement const * const InputLayoutArray, int const NumElements)
			{
				InputLayoutElements.clear();
				InputLayoutElements.insert(InputLayoutElements.begin(), InputLayoutArray, InputLayoutArray + NumElements);

				LayoutSize = 0;

				for (SInputLayoutElement const & Element : InputLayoutElements)
				{
					switch (Element.Type)
					{
					case EAttributeType::Double:
						LayoutSize += 8 * Element.Components;
						break;
					case EAttributeType::Float:
					case EAttributeType::Int:
					case EAttributeType::UnsignedInt:
						LayoutSize += 4 * Element.Components;
						break;
					}
				}
			}

			void CInstanceBuffer::SetInstanceCount(int const InstanceCount)
			{
				this->InstanceCount = InstanceCount;
			}

		}
	}
}
