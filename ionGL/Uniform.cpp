
#include "Uniform.h"
#include "Utilities.h"

#include <ionMath.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>


namespace ion
{
	namespace GL
	{
		template <>
		void UniformTyped<float>::Bind(uint const Handle, float const & Value)
		{
			CheckedGLCall(glUniform1f(Handle, Value));
		}

		template <>
		void UniformTyped<int>::Bind(uint const Handle, int const & Value)
		{
			CheckedGLCall(glUniform1i(Handle, Value));
		}

		template <>
		void UniformTyped<glm::mat4>::Bind(uint const Handle, glm::mat4 const & Value)
		{
			CheckedGLCall(glUniformMatrix4fv(Handle, 1, GL_FALSE, glm::value_ptr(Value)));
		}

		template <>
		void UniformTyped<vec2f>::Bind(uint const Handle, vec2f const & Value)
		{
			CheckedGLCall(glUniform2f(Handle, Value[0], Value[1]));
		}

		template <>
		void UniformTyped<vec3f>::Bind(uint const Handle, vec3f const & Value)
		{
			CheckedGLCall(glUniform3f(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void UniformTyped<vec4f>::Bind(uint const Handle, vec4f const & Value)
		{
			CheckedGLCall(glUniform4f(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void UniformTyped<color3f>::Bind(uint const Handle, color3f const & Value)
		{
			CheckedGLCall(glUniform3f(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void UniformTyped<color4f>::Bind(uint const Handle, color4f const & Value)
		{
			CheckedGLCall(glUniform4f(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void UniformTyped<vec2i>::Bind(uint const Handle, vec2i const & Value)
		{
			CheckedGLCall(glUniform2i(Handle, Value[0], Value[1]));
		}

		template <>
		void UniformTyped<vec3i>::Bind(uint const Handle, vec3i const & Value)
		{
			CheckedGLCall(glUniform3i(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void UniformTyped<vec4i>::Bind(uint const Handle, vec4i const & Value)
		{
			CheckedGLCall(glUniform4i(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void UniformTyped<color3i>::Bind(uint const Handle, color3i const & Value)
		{
			CheckedGLCall(glUniform3i(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void UniformTyped<color4i>::Bind(uint const Handle, color4i const & Value)
		{
			CheckedGLCall(glUniform4i(Handle, Value[0], Value[1], Value[2], Value[3]));
		}

		template <>
		void UniformTyped<vec2u>::Bind(uint const Handle, vec2u const & Value)
		{
			CheckedGLCall(glUniform2ui(Handle, Value[0], Value[1]));
		}

		template <>
		void UniformTyped<vec3u>::Bind(uint const Handle, vec3u const & Value)
		{
			CheckedGLCall(glUniform3ui(Handle, Value[0], Value[1], Value[2]));
		}

		template <>
		void UniformTyped<vec4u>::Bind(uint const Handle, vec4u const & Value)
		{
			CheckedGLCall(glUniform4ui(Handle, Value[0], Value[1], Value[2], Value[3]));
		}
	}
}
