
/*!
\file ionContainer.h
\ingroup ionCore
\brief Helper functions for working with std containers such as map and vector
*/


#pragma once

#include "ionTypes.h"
#include "ionSmartPointer.h"

#include <algorithm>
#include <functional>


namespace ion
{

	//! \ingroup ionCore
	template <typename T, typename U>
	U * ConditionalMapAccess(map<T, U *> const & Map, T const Key)
	{
		auto Iterator = Map.find(Key);

		if (Iterator != Map.end())
			return Iterator->second;

		return nullptr;
	}

	//! \ingroup ionCore
	template <typename T, typename U>
	SharedPointer<U> ConditionalMapAccess(map<T, SharedPointer<U>> const & Map, T const Key)
	{
		auto Iterator = Map.find(Key);

		if (Iterator != Map.end())
			return Iterator->second;

		return nullptr;
	}

	//! \ingroup ionCore
	template <typename T, typename U>
	U * ConditionalMapAccess(unordered_map<T, U *> const & Map, T const Key)
	{
		auto Iterator = Map.find(Key);

		if (Iterator != Map.end())
			return Iterator->second;

		return 0;
	}

	//! \ingroup ionCore
	template <typename T, typename U>
	bool CheckMapAccess(map<T, U> const & Map, T const Key)
	{
		return Map.find(Key) != Map.end();
	}

	//! \ingroup ionCore
	template <typename T, typename U>
	bool TryMapAccess(map<T, U> const & Map, T const Key, U & Value)
	{
		auto Iterator = Map.find(Key);

		if (Iterator != Map.end())
		{
			Value = Iterator->second;
			return true;
		}

		return false;
	}

	//! \ingroup ionCore
	template <typename T, typename U>
	set<T> KeySet(map<T, U> const & Map)
	{
		set<T> Return;

		for (auto it : Map)
			Return.insert(it.first);

		return Return;
	}

	//! \ingroup ionCore
	template <typename T>
	void AddAtEnd(vector<T> & A, vector<T> const & B)
	{
		A.insert(A.end(), B.begin(), B.end());
	}

	//! \ingroup ionCore
	template <typename T>
	void EraseRemove(vector<T> & A, T B)
	{
		A.erase(std::remove(std::begin(A), std::end(A), B), std::end(A));
	}

	//! \ingroup ionCore
	template <typename T, typename U>
	void EraseRemove(vector<T> & A, U B)
	{
		A.erase(std::remove(std::begin(A), std::end(A), B), std::end(A));
	}

	//! \brief Deletes every pointer element of a vector and then clears the vector
	template <typename T>
	void DeleteAndClear(vector<T> & A)
	{
		std::for_each(A.begin(), A.end(), [](T ptr) { delete ptr; });
		A.clear();
	}

}
