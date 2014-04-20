
#pragma once

#include <ionCore.h>


class IUniform
{

public:

	virtual void Bind(uint const Handle) const = 0;

};

template <typename T>
class SUniform : public IUniform
{

public:

	virtual T const & GetValue() const = 0;

	void Bind(uint const Handle) const
	{
		Bind(Handle, GetValue());
	}

	static void Bind(uint const Handle, T const & Value);

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
static sharedPtr<IUniform const> BindUniformReference(T const & uniform)
{
	return sharedPtr<IUniform const>(new SUniformReference<T>(uniform));
}

template <typename T>
static sharedPtr<IUniform const> BindUniformValue(T const & uniform)
{
	return sharedPtr<IUniform const>(new SUniformValue<T>(uniform));
}

template <typename T>
static sharedPtr<IUniform const> BindUniform(T const & uniform)
{
	return BindUniformReference(uniform);
}
