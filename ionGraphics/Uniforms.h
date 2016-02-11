
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Enums.h"


namespace ion
{
	namespace Graphics
	{

		class IUniform
		{

		public:

			virtual void const * GetData() const = 0;
			virtual EValueType GetType() const = 0;
			virtual size_t GetSize() const = 0;

		};

		template <typename T>
		class IUniformTyped : public IUniform
		{

		public:

			EValueType GetType() const;

			size_t GetSize() const
			{
				return sizeof(T);
			}

		};


		template <typename T>
		class CUniformReference : public IUniformTyped<T>
		{

		public:

			T const * Value;

			CUniformReference()
				: Value(0)
			{}

			CUniformReference(T const * value)
				: Value(value)
			{}

			CUniformReference(T const & value)
				: Value(& value)
			{}

			void const * GetData() const
			{
				return Value;
			}

		};

		template <typename T>
		class CUniformValue : public IUniformTyped<T>
		{

		public:

			T Value;

			CUniformValue()
			{}

			CUniformValue(T const & value)
				: Value(value)
			{}

			void const * GetData() const
			{
				return & Value;
			}

			CUniformValue & operator = (T const & value)
			{
				Value = value;
				return * this;
			}

			operator T() const
			{
				return Value;
			}

		};

	}
}
