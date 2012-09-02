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

public:

	virtual T const & getValue() const = 0;

	void bind(GLuint const handle, CShaderContext & shaderContext) const
	{
		shaderContext.uniform(handle, getValue());
	}

	void bind(GLuint const handle) const
	{
		CShaderContext::uniform(handle, getValue());
	}

};

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
static smartPtr<IUniform const> BindUniformReference(T const & uniform)
{
	return smartPtr<IUniform const>(new SUniformReference<T>(uniform));
}

template <typename T>
static smartPtr<IUniform const> BindUniformValue(T const & uniform)
{
	return smartPtr<IUniform const>(new SUniformValue<T>(uniform));
}

template <typename T>
static smartPtr<IUniform const> BindUniform(T const & uniform)
{
	return BindUniformReference(uniform);
}

#endif
