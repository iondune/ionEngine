
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

			class CInputLayout
			{

			public:

				CInputLayout(ID3D11Device * Device, vector<SInputLayoutElement> const & LayoutElements);
				~CInputLayout();

				ID3D11InputLayout * InputLayout = nullptr;

			};

			class CVertexBuffer : public IVertexBuffer
			{

			public:

				CVertexBuffer(ID3D11Device * Device);
				~CVertexBuffer();

				void UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements);
				void UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements);
				void SetInputLayout(SInputLayoutElement const * const InputLayoutArray, int const NumElements);
				void SetInstancingEnabled(bool const Enabled);


				ID3D11Device * Device = nullptr;
				ID3D11Buffer * VertexBuffer = nullptr;
				vector<SInputLayoutElement> InputLayoutElements;

				CInputLayout * InputLayout = nullptr;

				bool Instancing = false;

			};

		}
	}
}
