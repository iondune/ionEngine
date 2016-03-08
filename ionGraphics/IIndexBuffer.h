
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

			template <typename T>
			void UploadData(vector<T> const & Data);

			virtual void UploadData(void const * Data, size_t const Elements, EValueType const ValueType) = 0;

		};

	}
}
