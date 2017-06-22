
/*!
\file ionClass.h
\ingroup ionCore
\brief Methods and classes for rudimentary reflection and other class related functionality.
*/

#pragma once

#include <ionConfig.h>

#include <typeinfo>


namespace ion
{

	//! \brief Lightweight wrapper for std::type_info that enables sorting (e.g. for use in a std::map)
	//! \ingroup ionCore
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

	//! \brief Check whether an object is an instance of a type
	//! \ingroup ionCore
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
	//! \ingroup ionCore
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
	//! \ingroup ionCore
	//! \param Object Pointer to object to cast
	//! \tparam T Type to cast to
	//! \tparam U Type to cast from, type of Object
	template <typename T, typename U>
	T * As(U * Object)
	{
		return dynamic_cast<T *>(Object);
	}

	//! \brief Casts a constant object as a different type, performing a validity check
	//! \ingroup ionCore
	//! \param Object Pointer to object to cast
	//! \tparam T Type to cast to
	//! \tparam U Type to cast from, type of Object
	template <typename T, typename U>
	T const * As(U const * Object)
	{
		return dynamic_cast<T const *>(Object);
	}

	//! \brief Casts an object as a different type, performing a validity check
	//! \ingroup ionCore
	//! \param Object Reference to object to cast
	//! \tparam T Type to cast to
	//! \tparam U Type to cast from, type of Object
	template <typename T, typename U>
	T & As(U & Object)
	{
		return * dynamic_cast<T *>(& Object);
	}

	//! \brief Casts a constant object as a different type, performing a validity check
	//! \ingroup ionCore
	//! \param Object Reference to object to cast
	//! \tparam T Type to cast to
	//! \tparam U Type to cast from, type of Objec
	template <typename T, typename U>
	T const & As(U const & Object)
	{
		return * dynamic_cast<T const *>(& Object);
	}

}
