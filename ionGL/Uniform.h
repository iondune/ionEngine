
#pragma once

#include <ionCore.h>


namespace ion
{
	namespace GL
	{
		class Uniform
		{

		public:

			virtual void Bind(uint const Handle) const = 0;

		};

		template <typename T>
		class UniformTyped : public Uniform
		{

		public:

			virtual T const & GetValue() const = 0;

			void Bind(uint const Handle) const
			{
				Bind(Handle, GetValue());
			}

			static void Bind(uint const Handle, T const & Value);

		};

		template <typename T>
		class UniformReference : public UniformTyped<T>
		{

		public:

			T const * Value;

			UniformReference()
				: Value(0)
			{}

			UniformReference(T const * value)
				: Value(value)
			{}

			UniformReference(T const & value)
				: Value(& value)
			{}

			T const & GetValue() const
			{
				return * Value;
			}

		};

		template <typename T>
		class UniformValue : public UniformTyped<T>
		{

		public:

			T Value;

			UniformValue()
			{}

			UniformValue(T const & value)
				: Value(value)
			{}

			T const & GetValue() const
			{
				return Value;
			}

		};

		template <typename T>
		static sharedPtr<Uniform const> BindUniformReference(T const & uniform)
		{
			return sharedPtr<Uniform const>(new UniformReference<T>(uniform));
		}

		template <typename T>
		static sharedPtr<Uniform const> BindUniformValue(T const & uniform)
		{
			return sharedPtr<Uniform const>(new UniformValue<T>(uniform));
		}

		template <typename T>
		static sharedPtr<Uniform const> BindUniform(T const & uniform)
		{
			return BindUniformReference(uniform);
		}
	}
}
