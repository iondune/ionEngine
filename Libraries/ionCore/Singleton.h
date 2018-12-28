
#pragma once

#include "ionTypes.h"


namespace ion
{

	//! \brief Base class for Singleton design pattern implementation
	//! \ingroup ionCore
	template <class Implementation>
	class Singleton
	{

		Singleton(Singleton const &) = delete;
		Singleton & operator = (Singleton const &) = delete;

	public:

		static Implementation & Get()
		{
			static Implementation * Instance = 0;

			if (! Instance)
				Instance = new Implementation();

			return * Instance;
		}

		static Implementation * GetPointer()
		{
			return & Get();
		}

	protected:

		Singleton()
		{}

	};

}
