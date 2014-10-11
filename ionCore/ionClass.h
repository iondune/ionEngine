
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

//! \brief Casts an object as a different type, performing a validity check
//! \param Object Pointer to object to cast
//! \tparam T Type to cast to
//! \tparam U Type to cast from, type of Object
template <typename T, typename U>
T * As(U * Object)
{
	return dynamic_cast<T *>(Object);
}

//! \brief Casts a constant object as a different type, performing a validity check
//! \param Object Pointer to object to cast
//! \tparam T Type to cast to
//! \tparam U Type to cast from, type of Object
template <typename T, typename U>
T const * As(U const * Object)
{
	return dynamic_cast<T const *>(Object);
}

//! \brief Casts an object as a different type, performing a validity check
//! \param Object Reference to object to cast
//! \tparam T Type to cast to
//! \tparam U Type to cast from, type of Object
template <typename T, typename U>
T & As(U & Object)
{
	return * dynamic_cast<T *>(& Object);
}

//! \brief Casts a constant object as a different type, performing a validity check
//! \param Object Reference to object to cast
//! \tparam T Type to cast to
//! \tparam U Type to cast from, type of Objec
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

protected:

	Singleton()
	{}

};

template <class T>
class SingletonPointer
{

public:

	T * operator ->()
	{
		return GetReference();
	}

	T * Get()
	{
		return GetReference();
	}

	operator T*()
	{
		return GetReference();
	}

	T const * operator ->() const
	{
		return GetReference();
	}

	T const * Get() const
	{
		return GetReference();
	}

	operator T const *() const
	{
		return GetReference();
	}

private:

	mutable T * Reference = 0;

	T * GetReference()
	{
		if (! Reference)
			Reference = T::GetPtr();
		return Reference;
	}

	T const * GetReference() const
	{
		if (! Reference)
			Reference = T::GetPtr();
		return Reference;
	}

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
