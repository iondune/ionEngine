
#include "Enums.h"


namespace ion
{
	namespace Graphics
	{

		size_t GetValueTypeSize(EValueType const ValueType)
		{
			switch (ValueType)
			{
			case EValueType::Float:
				return sizeof(float);
			case EValueType::Float2:
				return sizeof(float) * 2;
			case EValueType::Float3:
				return sizeof(float) * 3;
			case EValueType::Float4:
				return sizeof(float) * 4;
			case EValueType::Matrix4x4:
				return sizeof(float) * 4 * 4;
			case EValueType::Double:
				return sizeof(double);
			case EValueType::SignedInt8:
				return sizeof(Int8);
			case EValueType::SignedInt16:
				return sizeof(Int16);
			case EValueType::SignedInt32:
				return sizeof(Int32);
			case EValueType::UnsignedInt8:
				return sizeof(Uint8);
			case EValueType::UnsignedInt16:
				return sizeof(Uint16);
			case EValueType::UnsignedInt32:
				return sizeof(Uint32);
			default:
				return 0;
			}
		}

		string GetValueTypeString(EValueType const ValueType)
		{
			switch (ValueType)
			{
			case EValueType::Float:
				return "Float";
			case EValueType::Float2:
				return "Float2";
			case EValueType::Float3:
				return "Float3";
			case EValueType::Float4:
				return "Float4";
			case EValueType::Matrix4x4:
				return "Matrix4x4";
			case EValueType::Double:
				return "Double";
			case EValueType::SignedInt8:
				return "SignedInt8";
			case EValueType::SignedInt16:
				return "SignedInt16";
			case EValueType::SignedInt32:
				return "SignedInt32";
			case EValueType::UnsignedInt8:
				return "UnsignedInt8";
			case EValueType::UnsignedInt16:
				return "UnsignedInt16";
			case EValueType::UnsignedInt32:
				return "UnsignedInt32";
			default:
				return "Unknown";
			}
		}

		size_t GetScalarTypeSize(EScalarType const ScalarType)
		{
			switch (ScalarType)
			{
			case EScalarType::Float:
				return sizeof(float);
			case EScalarType::Double:
				return sizeof(double);
			case EScalarType::SignedInt8:
				return sizeof(Int8);
			case EScalarType::SignedInt16:
				return sizeof(Int16);
			case EScalarType::SignedInt32:
				return sizeof(Int32);
			case EScalarType::UnsignedInt8:
				return sizeof(Uint8);
			case EScalarType::UnsignedInt16:
				return sizeof(Uint16);
			case EScalarType::UnsignedInt32:
				return sizeof(Uint32);
			default:
				return 0;
			}
		}

		size_t GetAttributeTypeSize(EAttributeType const AttributeType)
		{
			switch (AttributeType)
			{
			case EAttributeType::Float:
				return sizeof(float);
			case EAttributeType::Double:
				return sizeof(double);
			case EAttributeType::Int:
				return sizeof(int);
			case EAttributeType::UnsignedInt:
				return sizeof(uint);
			default:
				return 0;
			}
		}

		string GetAttributeTypeString(EAttributeType const AttributeType)
		{
			switch (AttributeType)
			{
			case EAttributeType::Float:
				return "Float";
			case EAttributeType::Double:
				return "Double";
			case EAttributeType::Int:
				return "Int";
			case EAttributeType::UnsignedInt:
				return "Unsigned Int";
			default:
				return "Unknown";
			}
		}

	}
}
