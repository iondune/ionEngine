
#pragma once

#include "ionStandardLibrary.h"
#include "ionClass.h"


template <typename TComponent>
class IEntity
{

public:
	
	template <typename T>
	void AddComponent(T * Component)
	{
		Components.insert(typeid(T), Component);
	}

	template <typename T>
	pair<typename multimap<Type, TComponent *>::iterator, typename multimap<Type, TComponent *>::iterator> GetComponents()
	{
		return Components.equal_range(typeid(T));
	}
	
	template <typename T>
	int ExpectSingleComponent(T * & Component)
	{
		int Count = Components.count(typeid(T));
		if (Count >= 1)
			Component = *Components.find(typeid(T));

		return Count;
	}

protected:

	multimap<Type, TComponent *> Components;

};
