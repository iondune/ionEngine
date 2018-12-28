
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

			class CIndexBuffer : public IIndexBuffer
			{

			public:

				uint Handle = 0;
				size_t Size = 0;

				~CIndexBuffer();

				void UploadData(void const * Data, size_t const Elements, EValueType const ValueType);

			};

		}
	}
}
