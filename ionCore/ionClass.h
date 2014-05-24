
/*!
\file ionClass.h
\brief Methods and classes for rudimentary reflection and other class related functionality.
*/

#pragma once

#include <ionConfig.h>

#include <typeinfo>


//! \brief Check whether an object is an instance of a type
//! \param Object Object to check the type of
//! \tparam T Type to check Object against
//! \tparam U Actual type of Object (best left inferred)
//!
//! Implemented by checking the return value of dynamic_cast.
//! Relies on RTTI.
template <typename T, typename U>
bool InstanceOf(U * Object)
{
	return dynamic_cast<T const *>(Object) != 0;
}

//! \brief Check whether an object is an instance of a type
//! \param Object Object to check the type of
//! \tparam T Type to check Object against
//! \tparam U Actual type of Object (best left inferred)
//!
//! Implemented by checking the return value of dynamic_cast.
//! Relies on RTTI.
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

struct Type
{
	Type(std::type_info const & value)
		: Value(value)
	{}

	bool operator <(Type const & other) const
	{
		return Value.before(other.Value);
	}

	std::type_info const & Value;
};
