
#include "CVertexBuffer.h"
#include "Utilities.h"

#include <d3dcompiler.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

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
