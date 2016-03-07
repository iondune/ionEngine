
#include "IUniform.h"


namespace ion
{
	namespace Graphics
	{

		size_t GetUniformTypeSize(EUniformType const UniformType)
		{
			switch (UniformType)
			{
			case EUniformType::Float:
				return sizeof(float);
			case EUniformType::Float2:
				return sizeof(float) * 2;
			case EUniformType::Float3:
				return sizeof(float) * 3;
			case EUniformType::Float4:
				return sizeof(float) * 4;
			case EUniformType::Matrix4x4:
				return sizeof(float) * 4 * 4;
			case EUniformType::Int:
				return sizeof(int);
			case EUniformType::Int2:
				return sizeof(int) * 2;
			case EUniformType::Int3:
				return sizeof(int) * 3;
			case EUniformType::Int4:
				return sizeof(int) * 4;
			default:
				return 0;
			}
		}

		string GetUniformTypeString(EUniformType const UniformType)
		{
			switch (UniformType)
			{
			case EUniformType::Float:
				return "Float";
			case EUniformType::Float2:
				return "Float2";
			case EUniformType::Float3:
				return "Float3";
			case EUniformType::Float4:
				return "Float4";
			case EUniformType::Matrix4x4:
				return "Matrix4x4";
			case EUniformType::Int:
				return "Int";
			case EUniformType::Int2:
				return "Int2";
			case EUniformType::Int3:
				return "Int3";
			case EUniformType::Int4:
				return "Int4";
			default:
				return "Unknown";
			}
		}

		template <>
		EUniformType IUniformTyped<float>::GetType() const
		{
			return EUniformType::Float;
		}

		template <>
		EUniformType IUniformTyped<vec2f>::GetType() const
		{
			return EUniformType::Float2;
		}

		template <>
		EUniformType IUniformTyped<vec3f>::GetType() const
		{
			return EUniformType::Float3;
		}

		template <>
		EUniformType IUniformTyped<vec4f>::GetType() const
		{
			return EUniformType::Float4;
		}

		template <>
		EUniformType IUniformTyped<color3f>::GetType() const
		{
			return EUniformType::Float3;
		}

		template <>
		EUniformType IUniformTyped<color4f>::GetType() const
		{
			return EUniformType::Float4;
		}

		template <>
		EUniformType IUniformTyped<glm::mat4>::GetType() const
		{
			return EUniformType::Matrix4x4;
		}

		template <>
		EUniformType IUniformTyped<int>::GetType() const
		{
			return EUniformType::Int;
		}

		template <>
		EUniformType IUniformTyped<vec2i>::GetType() const
		{
			return EUniformType::Int2;
		}

		template <>
		EUniformType IUniformTyped<vec3i>::GetType() const
		{
			return EUniformType::Int3;
		}

		template <>
		EUniformType IUniformTyped<vec4i>::GetType() const
		{
			return EUniformType::Int4;
		}

	}
}
