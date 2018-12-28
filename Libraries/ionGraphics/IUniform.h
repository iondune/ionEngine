
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Enums.h"


namespace ion
{
	namespace Graphics
	{

		//! \brief Possible types for uniforms
		//! \ingroup ionGraphics
		enum class EUniformType
		{
			Float = 0,
			Float2 = 1,
			Float3 = 2,
			Float4 = 3,
			Int = 4,
			Int2 = 5,
			Int3 = 6,
			Int4 = 7,
			Matrix4x4 = 8,
			FloatArray = 9,
			Float2Array = 10,
			Float3Array = 11,
			Matrix4x4Array = 12,
			Bool = 13,
			UnsignedInt = 14,
			Unknown = 1000,
		};

		//! \brief Converts uniform enum to equivalent string form
		//! \ingroup ionGraphics
		string GetUniformTypeString(EUniformType const UniformType);

		//! \brief Abstract interface for anything which can be uploaded as a shader uniform
		//! \ingroup ionGraphics
		class IUniform
		{

		public:

			virtual void const * GetData() const = 0;
			virtual EUniformType GetType() const = 0;
			virtual size_t GetSize() const = 0;

		};

		//! \brief Abstract interface for IUniform with known type
		//! \ingroup ionGraphics
		template <typename T>
		class IUniformTyped : public IUniform
		{

		public:

			EUniformType GetType() const;

			size_t GetSize() const
			{
				return sizeof(T);
			}

		};

		//! \brief Implementation of IUniformTyped that stores a (non-owning) reference to value
		//! \ingroup ionGraphics
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

			void const * GetData() const
			{
				return Value;
			}

		};

		//! \brief Implementation of IUniformTyped that uses a given lambda callback to provide uniform value
		//! \ingroup ionGraphics
		template <typename T>
		class CUniformCallback : public IUniformTyped<T>
		{

		public:

			std::function<T()> Callback;

			CUniformCallback(std::function<T()> const callback)
				: Callback(callback)
			{}

			void const * GetData() const
			{
				Temporary = Callback();
				return &Temporary;
			}

		protected:

			mutable T Temporary;

		};

		//! \brief Implementation of IUniformTyped that stores a copy of a given value for uniform upload
		//! \ingroup ionGraphics
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

			operator T () const
			{
				return Value;
			}

		};

		//! \brief Helper class to easily add a uniform as a member or local variable
		//! \ingroup ionGraphics
		template <typename T>
		class CUniform
		{

		public:

			SharedPointer<CUniformValue<T>> Uniform;

			CUniform()
				: Uniform(MakeShared<CUniformValue<T>>())
			{}

			CUniform(CUniform<T> const & other)
				: Uniform(MakeShared<CUniformValue<T>>())
			{
				Uniform->Value = other.Uniform->Value;
			}

			CUniform(CUniform<T> && other)
				: Uniform(other.Uniform)
			{
				other.Uniform = nullptr;
			}

			CUniform(T const & value)
				: Uniform(MakeShared<CUniformValue<T>>())
			{
				Uniform->Value = value;
			}

			CUniform<T> & operator = (CUniform<T> const & other)
			{
				Uniform->Value = other.Uniform->Value;
				return * this;
			}

			CUniform<T> & operator = (CUniform<T> && other)
			{
				Uniform = other.Uniform;
				other.Uniform = nullptr;
				return * this;
			}

			CUniform<T> & operator = (T const & value)
			{
				Uniform->Value = value;
				return * this;
			}

			T * operator ->()
			{
				return & Uniform->Value;
			}

			operator T () const
			{
				return Uniform->Value;
			}

			operator SharedPointer<IUniform> ()
			{
				return Uniform;
			}

			T & Get()
			{
				return Uniform->Value;
			}

			CUniform<T> & operator ++ ()
			{
				Uniform->Value ++;
				return * this;
			}

			CUniform<T> & operator ++ (int)
			{
				Uniform->Value ++;
				return * this;
			}

			CUniform<T> & operator -- ()
			{
				Uniform->Value --;
				return * this;
			}

			CUniform<T> & operator -- (int)
			{
				Uniform->Value --;
				return * this;
			}

			CUniform<T> & operator += (T const & value)
			{
				Uniform->Value += value;
				return * this;
			}

			CUniform<T> & operator -= (T const & value)
			{
				Uniform->Value -= value;
				return * this;
			}

			CUniform<T> & operator *= (T const & value)
			{
				Uniform->Value *= value;
				return * this;
			}

			CUniform<T> & operator /= (T const & value)
			{
				Uniform->Value /= value;
				return * this;
			}

		};

	}
}
