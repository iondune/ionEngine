
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

			class CIndexBuffer : public IIndexBuffer
			{

			public:

				CIndexBuffer(ID3D11Device * Device);
				~CIndexBuffer();

				void UploadData(void const * Data, size_t const Elements, EValueType const ValueType);

				size_t Size = 0;

				ID3D11Device * Device = nullptr;
				ID3D11Buffer * IndexBuffer = nullptr;

			};

		}
	}
}
