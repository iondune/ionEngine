
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace Graphics
	{

		//! \brief Standard type enum used through module
		//! \ingroup ionGraphics
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

		//! \brief Value types that exclude vector types
		//! \ingroup ionGraphics
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

		//! \brief Possible types for attributes i.e. vertex buffer contents
		//! \ingroup ionGraphics
		enum EAttributeType
		{
			Float       = 0,
			Int         = 1,
			UnsignedInt = 2,
			Double      = 3,
		};

		//! \brief Gets the sizeof() for a given type
		//! \ingroup ionGraphics
		size_t GetValueTypeSize(EValueType const ValueType);

		//! \brief Gets the string equivalent of the given enum
		//! \ingroup ionGraphics
		string GetValueTypeString(EValueType const ValueType);

		//! \brief Gets the sizeof() for a given attribute type
		//! \ingroup ionGraphics
		size_t GetAttributeTypeSize(EAttributeType const AttributeType);

		//! \brief Gets the string equivalent of the given enum
		//! \ingroup ionGraphics
		string GetAttributeTypeString(EAttributeType const AttributeType);

	}
}
