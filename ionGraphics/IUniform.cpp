
#include "IUniform.h"


namespace ion
{
	namespace Graphics
	{

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
			case EUniformType::Bool:
				return "Bool";
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
		EUniformType IUniformTyped<vector<float>>::GetType() const
		{
			return EUniformType::FloatArray;
		}

		template <>
		EUniformType IUniformTyped<vec2f>::GetType() const
		{
			return EUniformType::Float2;
		}

		template <>
		EUniformType IUniformTyped<vector<vec2f>>::GetType() const
		{
			return EUniformType::Float2Array;
		}

		template <>
		EUniformType IUniformTyped<vec3f>::GetType() const
		{
			return EUniformType::Float3;
		}

		template <>
		EUniformType IUniformTyped<vector<vec3f>>::GetType() const
		{
			return EUniformType::Float3Array;
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
		EUniformType IUniformTyped<vector<glm::mat4>>::GetType() const
		{
			return EUniformType::Matrix4x4Array;
		}

		template <>
		EUniformType IUniformTyped<int>::GetType() const
		{
			return EUniformType::Int;
		}

		template <>
		EUniformType IUniformTyped<bool>::GetType() const
		{
			return EUniformType::Bool;
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
