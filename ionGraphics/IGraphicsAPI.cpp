
#include "IGraphicsAPI.h"


size_t ion::Graphics::GetValueTypeSize(EValueType const ValueType)
{
	switch (ValueType)
	{
	case EValueType::Float:
		return sizeof(float);
	case EValueType::Double:
		return sizeof(double);
	case EValueType::SignedInt8:
		return sizeof(s8);
	case EValueType::SignedInt16:
		return sizeof(s16);
	case EValueType::SignedInt32:
		return sizeof(s32);
	case EValueType::UnsignedInt8:
		return sizeof(u8);
	case EValueType::UnsignedInt16:
		return sizeof(u16);
	case EValueType::UnsignedInt32:
		return sizeof(u32);
	default:
		return 0;
	}
}
