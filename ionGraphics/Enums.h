
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Graphics
	{

		enum class EValueType
		{
			Error         = 0,
			Float         = 1,
			Float2        = 2,
			Float3        = 3,
			Float4        = 4,
			Matrix4x4     = 5,
			Double        = 6,
			SignedInt8    = 7,
			SignedInt16   = 8,
			SignedInt32   = 9,
			UnsignedInt8  = 10,
			UnsignedInt16 = 11,
			UnsignedInt32 = 12,
		};

		enum class EScalarType
		{
			Error         = 0,
			Float         = 1,
			Double        = 2,
			SignedInt8    = 3,
			SignedInt16   = 4,
			SignedInt32   = 5,
			UnsignedInt8  = 6,
			UnsignedInt16 = 7,
			UnsignedInt32 = 8,
		};

		enum EAttributeType
		{
			Float       = 0,
			Int         = 1,
			UnsignedInt = 2,
			Double      = 3,
		};

		size_t GetValueTypeSize(EValueType const ValueType);
		size_t GetAttributeTypeSize(EAttributeType const AttributeType);

	}
}
