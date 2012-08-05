#ifndef _CABBAGE_SCENE_SUNIFORM_H_INCLUDED_
#define _CABBAGE_SCENE_SUNIFORM_H_INCLUDED_

// Core
#include <boost/shared_ptr.hpp>
#include <glm/gtc/type_ptr.hpp>

// Scene
#include "CShaderContext.h"


class IUniform
{

public:

	virtual void bind(GLuint const handle, CShaderContext & shaderContext) const = 0;
	virtual void bind(GLuint const handle) const = 0;

};

template <typename T>
class SUniform : public IUniform
{

private:

	void TypeCannotBeBoundToShader();

public:

	virtual T const & getValue() const = 0;

	void bind(GLuint const handle, CShaderContext & shaderContext) const
	{
		shaderContext.uniform(handle, getValue());
	}

	void bind(GLuint const handle) const
	{
		TypeCannotBeBoundToShader();
	}

};

void SUniform<GLfloat>::bind(GLuint const handle) const
{
	glUniform1f(handle, getValue());
}

void SUniform<SVector3<GLfloat> >::bind(GLuint const handle) const
{
	glUniform3f(handle, getValue().X, getValue().Y, getValue().Z);
}

void SUniform<SColor>::bind(GLuint const handle) const
{
	glUniform3f(handle, getValue().Red, getValue().Green, getValue().Blue);
}

void SUniform<GLint>::bind(GLuint const handle) const
{
	glUniform1i(handle, getValue());
}

/*
void SUniform<SVector2Reference<GLint> >::bind(GLuint const handle) const
{
	glUniform2i(handle, getValue().X, getValue().Y);
}

void SUniform<SVector3Reference<GLint> >::bind(GLuint const handle) const
{
	glUniform3i(handle, getValue().X, getValue().Y, getValue().Z);
}
*/ // Temporarily removed because of compiler warnings (needs to be implemented in ShaderContext as well)

void SUniform<glm::mat4>::bind(GLuint const handle) const
{
	glUniformMatrix4fv(handle, 1, GL_FALSE, glm::value_ptr(getValue()));
}

void SUniform<STransformation3>::bind(GLuint const handle) const
{
	glUniformMatrix4fv(handle, 1, GL_FALSE, glm::value_ptr(getValue()()));
}

template <typename T>
class SUniformReference : public SUniform<T>
{

public:

	T const * Value;

	SUniformReference()
		: Value(0)
	{}

	SUniformReference(T const * value)
		: Value(value)
	{}

	SUniformReference(T const & value)
		: Value(& value)
	{}

	T const & getValue() const
	{
		return * Value;
	}

};

template <typename T>
class SUniformValue : public SUniform<T>
{

public:

	T Value;

	SUniformValue(T const & value)
		: Value(value)
	{}

	T const & getValue() const 
	{
		return Value;
	}

};

template <typename T>
static boost::shared_ptr<IUniform const> BindUniform(T const & uniform)
{
	return boost::shared_ptr<IUniform const>(new SUniformReference<T>(uniform));
}

#endif
