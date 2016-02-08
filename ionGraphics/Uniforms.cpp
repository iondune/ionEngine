
#include "Uniforms.h"


namespace ion
{
	namespace Graphics
	{

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
