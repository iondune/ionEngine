
#pragma once

#include "ionStandardLibrary.h"
#include "ionClass.h"


template <typename TComponent>
class IEntity
{

public:
	
	template <typename T>
	T * AddComponent(T * Component)
	{
		return (T *) Components.insert(pair<Type, TComponent *>(typeid(T), Component))->second;
	}

	template <typename T>
	pair<typename multimap<Type, TComponent *>::iterator, typename multimap<Type, TComponent *>::iterator> GetComponents()
	{
		return Components.equal_range(typeid(T));
	}

	template <typename T>
	int GetComponentCount() const
	{
		return Components.count(typeid(T));
	}
	
	template <typename T>
	int ExpectSingleComponent(T * & Component)
	{
		int Count = GetComponentCount<T>();
		if (Count >= 1)
			Component = (T *) Components.find(typeid(T))->second;

		return Count;
	}
	template <typename T>
	T * RequireSingleComponent()
	{
		int Count = GetComponentCount<T>();
		if (Count >= 1)
			return (T *) Components.find(typeid(T))->second;
		else
			return AddComponent(new T{});
	}

protected:

	multimap<Type, TComponent *> Components;

};
