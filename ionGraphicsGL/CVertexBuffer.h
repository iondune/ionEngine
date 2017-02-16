
#pragma once

#include <ionCore.h>
#include <ionMath.h>
#include <ionGraphics.h>

#include "Utilities.h"


namespace ion
{
	namespace Graphics
	{
		namespace GL
		{

			class CVertexBuffer : public IVertexBuffer
			{

			public:

				~CVertexBuffer();

				void UploadData(void const * const Data, size_t const DataSize, size_t const NumberOfElements);
				void UploadSubData(void const * const Data, size_t const DataSize, size_t const Offset, size_t const NumberOfElements);
				void SetInputLayout(SInputLayoutElement const * const InputLayout, int const NumElements);
				void SetInstancingEnabled(bool const Enabled);


				uint Handle = 0;
				vector<SInputLayoutElement> InputLayout;
				bool Instancing = false;

			};

		}
	}
}
