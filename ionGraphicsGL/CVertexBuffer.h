
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

				void UploadData(float const * const Data, size_t const Elements);
				void SetInputLayout(SInputLayoutElement * InputLayout, int const NumElements);
				void SetInstancingEnabled(bool const Enabled);


				uint Handle = 0;
				vector<SInputLayoutElement> InputLayout;
				bool Instancing = false;

			};

		}
	}
}
