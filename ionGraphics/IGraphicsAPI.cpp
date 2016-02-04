
#include "IGraphicsAPI.h"


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

		template <>
		EValueType IUniformTyped<float>::GetType() const
		{
			return EValueType::Float;
		}

		template <>
		EValueType IUniformTyped<vec2f>::GetType() const
		{
			return EValueType::Float2;
		}

		template <>
		EValueType IUniformTyped<vec3f>::GetType() const
		{
			return EValueType::Float3;
		}

		template <>
		EValueType IUniformTyped<vec4f>::GetType() const
		{
			return EValueType::Float4;
		}

		template <>
		EValueType IUniformTyped<color3f>::GetType() const
		{
			return EValueType::Float3;
		}

		template <>
		EValueType IUniformTyped<color4f>::GetType() const
		{
			return EValueType::Float4;
		}

		template <>
		EValueType IUniformTyped<glm::mat4>::GetType() const
		{
			return EValueType::Matrix4x4;
		}

		template <>
		EValueType IUniformTyped<int>::GetType() const
		{
			return EValueType::SignedInt32;
		}

	}
}
