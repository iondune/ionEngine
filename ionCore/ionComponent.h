
/*!
\file ionComponent.h
\ingroup ionCore
\brief Basic component-entity system driven by types

Basic Usage:

Derive your entity class from IEntity<T> where T is the base class of your
Entity class.
*/

#pragma once

#include "ionStandardLibrary.h"
#include "ionClass.h"


//! \brief Base class for Component-Entity design pattern implementation
//! \ingroup ionCore
template <typename TComponent>
class IEntity
{

public:

	//! \brief Add a component to this entity
	//! \param Component The component to add
	//! \tparam T The actual type of the component added (assumed derived from TComponent)
	//! \return The component that was added by this operation
	template <typename T>
	T * AddComponent(T * Component)
	{
		return (T *) Components.insert(pair<Type, TComponent *>(typeid(T), Component))->second;
	}

	//! \brief Get an iterator range of all components of a given type
	//! Note: Does not return elemtns of a type derived from T
	//! \tparam T Type of matched components
	template <typename T>
	pair<typename multimap<Type, TComponent *>::iterator, typename multimap<Type, TComponent *>::iterator> GetComponents()
	{
		return Components.equal_range(typeid(T));
	}

	//! \brief Get the number of components of a given type
	//! Note: Does not count elements of a type derived from T
	//! \tparam T Type of matched components
	template <typename T>
	size_t GetComponentCount() const
	{
		return Components.count(typeid(T));
	}

	template <typename T>
	size_t ExpectSingleComponent(T * & Component)
	{
		size_t Count = GetComponentCount<T>();
		if (Count >= 1)
			Component = (T *) Components.find(typeid(T))->second;

		return Count;
	}

	template <typename T>
	T * RequireSingleComponent()
	{
		size_t Count = GetComponentCount<T>();
		if (Count >= 1)
			return (T *) Components.find(typeid(T))->second;
		else
			return AddComponent(new T{});
	}

protected:

	multimap<Type, TComponent *> Components;

};
