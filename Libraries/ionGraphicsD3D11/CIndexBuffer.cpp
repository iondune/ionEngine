
#include "CIndexBuffer.h"
#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			CIndexBuffer::CIndexBuffer(ID3D11Device * Device)
			{
				this->Device = Device;
			}

			CIndexBuffer::~CIndexBuffer()
			{
				if (IndexBuffer)
				{
					IndexBuffer->Release();
					IndexBuffer = nullptr;
				}
			}

			void CIndexBuffer::UploadData(void const * Data, size_t const NumElements, EValueType const ValueType)
			{
				if (IndexBuffer)
				{
					IndexBuffer->Release();
					IndexBuffer = nullptr;
				}

				D3D11_BUFFER_DESC IndexBufferDesc = {};
				IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				IndexBufferDesc.ByteWidth = (UINT) (sizeof(uint32_t) * NumElements);
				IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
				IndexBufferDesc.CPUAccessFlags = 0;

				if (IndexBufferDesc.ByteWidth)
				{
					D3D11_SUBRESOURCE_DATA InitData = {};
					InitData.pSysMem = Data;
					CheckedDXCall(Device->CreateBuffer(&IndexBufferDesc, &InitData, &IndexBuffer));
				}

				Size = (int) NumElements;
			}

		}
	}
}
