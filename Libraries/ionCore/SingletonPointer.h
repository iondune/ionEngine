
#pragma once

#include "Singleton.h"


namespace ion
{

	//! \brief Wraps a pointer to a singleton object
	//! \ingroup ionCore
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
				Reference = T::GetPointer();
			return Reference;
		}

		T const * GetReference() const
		{
			if (! Reference)
				Reference = T::GetPointer();
			return Reference;
		}

	};

}
