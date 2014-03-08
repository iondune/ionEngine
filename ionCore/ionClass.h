
#pragma once

#include <ionConfig.h>


template <typename T, typename U>
bool InstanceOf(U * Object)
{
	return dynamic_cast<T const *>(Object) != 0;
}

template <typename T, typename U>
bool InstanceOf(U & Object)
{
	return dynamic_cast<T const *>(& Object) != 0;
}

template <typename T, typename U>
T * As(U * Object)
{
	return dynamic_cast<T *>(Object);
}

template <typename T, typename U>
T const * As(U const * Object)
{
	return dynamic_cast<T const *>(Object);
}

template <typename T, typename U>
T & As(U & Object)
{
	return * dynamic_cast<T *>(& Object);
}

template <typename T, typename U>
T const & As(U const & Object)
{
	return * dynamic_cast<T const *>(& Object);
}

template <class Implementation>
class Singleton
{

	Singleton(Singleton const &);
	Singleton & operator = (Singleton const &);

protected:

	Singleton()
	{}

public:

	static Implementation & Get()
	{
		static Implementation * Instance = 0;

		if (! Instance)
			Instance = new Implementation();

		return * Instance;
	}

	static Implementation * GetPtr()
	{
		return & Get();
	}

};

template <class T>
struct SingletonPointer
{

	SingletonPointer()
		: Reference(T::Get())
	{}

	T * operator ->()
	{
		return & Reference;
	}

	T & Reference;

};
