
#pragma once

#include <ionCore.h>

#include "Enums.h"


namespace ion
{
	namespace Graphics
	{

		class IIndexBuffer
		{

		public:

			virtual ~IIndexBuffer()
			{}

			virtual void UploadData(void const * Data, size_t const Elements, EValueType const ValueType) = 0;

		};

	}
}
