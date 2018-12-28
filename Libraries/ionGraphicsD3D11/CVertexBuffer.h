
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include <D3D11.h>


namespace ion
{
	namespace Graphics
	{
		namespace D3D11
		{

			class CVertexBuffer : public IVertexBuffer
			{

			public:

				CVertexBuffer(ID3D11Device * Device);
				~CVertexBuffer();

				void UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements);
				void UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements);
				void SetInputLayout(SInputLayoutElement const * const InputLayoutArray, int const NumElements);


				ID3D11Device * Device = nullptr;
				ID3D11Buffer * VertexBuffer = nullptr;
				vector<SInputLayoutElement> InputLayoutElements;
				int LayoutSize = 0;

			};

			class CInstanceBuffer : public IInstanceBuffer
			{

			public:

				CInstanceBuffer(ID3D11Device * Device);
				~CInstanceBuffer();

				void UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements);
				void UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements);
				void SetInputLayout(SInputLayoutElement const * const InputLayoutArray, int const NumElements);
				void SetInstanceCount(int const InstanceCount);


				ID3D11Device * Device = nullptr;
				ID3D11Buffer * Buffer = nullptr;
				vector<SInputLayoutElement> InputLayoutElements;
				int LayoutSize = 0;

				int InstanceCount = 0;

			};

		}
	}
}
