
#include "SUniform.h"

#include <ionGL.h>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>


template <>
void SUniform<float>::Bind(uint const Handle, float const & Value)
{
	CheckedGLCall(glUniform1f(Handle, Value));
}

template <>
void SUniform<int>::Bind(uint const Handle, int const & Value)
{
	CheckedGLCall(glUniform1i(Handle, Value));
}

template <>
void SUniform<glm::mat4>::Bind(uint const Handle, glm::mat4 const & Value)
{
	CheckedGLCall(glUniformMatrix4fv(Handle, 1, GL_FALSE, glm::value_ptr(Value)));
}

template <>
void SUniform<STransformation3>::Bind(uint const Handle, STransformation3 const & Value)
{
	CheckedGLCall(glUniformMatrix4fv(Handle, 1, GL_FALSE, glm::value_ptr(Value())));
}

template <>
void SUniform<vec2f>::Bind(uint const Handle, vec2f const & Value)
{
	CheckedGLCall(glUniform2f(Handle, Value[0], Value[1]));
}

template <>
void SUniform<vec3f>::Bind(uint const Handle, vec3f const & Value)
{
	CheckedGLCall(glUniform3f(Handle, Value[0], Value[1], Value[2]));
}

template <>
void SUniform<vec4f>::Bind(uint const Handle, vec4f const & Value)
{
	CheckedGLCall(glUniform4f(Handle, Value[0], Value[1], Value[2], Value[3]));
}

template <>
void SUniform<vec2i>::Bind(uint const Handle, vec2i const & Value)
{
	CheckedGLCall(glUniform2i(Handle, Value[0], Value[1]));
}

template <>
void SUniform<vec3i>::Bind(uint const Handle, vec3i const & Value)
{
	CheckedGLCall(glUniform3i(Handle, Value[0], Value[1], Value[2]));
}

template <>
void SUniform<vec4i>::Bind(uint const Handle, vec4i const & Value)
{
	CheckedGLCall(glUniform4i(Handle, Value[0], Value[1], Value[2], Value[3]));
}

template <>
void SUniform<vec2u>::Bind(uint const Handle, vec2u const & Value)
{
	CheckedGLCall(glUniform2ui(Handle, Value[0], Value[1]));
}

template <>
void SUniform<vec3u>::Bind(uint const Handle, vec3u const & Value)
{
	CheckedGLCall(glUniform3ui(Handle, Value[0], Value[1], Value[2]));
}

template <>
void SUniform<vec4u>::Bind(uint const Handle, vec4u const & Value)
{
	CheckedGLCall(glUniform4ui(Handle, Value[0], Value[1], Value[2], Value[3]));
}
