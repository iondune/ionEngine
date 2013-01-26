#ifndef _ION_CORE_SVECTOR_H_INCLUDED_
#define _ION_CORE_SVECTOR_H_INCLUDED_

#include <cmath>

#include "ionUtils.h"


template <typename T, u32 Size>
class SVectorBase
{

private:
	
	SVectorBase & operator = (SVectorBase const &);

protected:

	SVectorBase()
	{}

public:

	static u32 const Dimension = Size;
	T Values[Dimension];
	mutable T OutOfBounds;
	
	//! Const member copy access
	//! Note: Out-of-bounds access returns a dummy value
	virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < Dimension ? Values[i] : OutOfBounds = 0);
	}
	
	//! Member reference access
	//! Note: Out-of-bounds access returns a dummy value
	virtual T & operator[] (int i)
	{
		return (i >= 0 && i < Dimension ? Values[i] : OutOfBounds = 0);
	}

	//! Sets all dimension values to 0
	void reset()
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] = 0;
	}

	//! Sets all dimension values to a single scalar
	void set(T in)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] = in;
	}

	//! Sets all dimension values by an input C-style array
	void set(T in[])
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] = in[i];
	}

	//! Length of vector
	T const length() const
	{
		T sum = 0;
		for (int i = 0; i < Dimension; ++ i)
			sum += sq(Values[i]);
		return (T) sqrt(sum);
	}

	//! Squared-length of vector (computationally fast)
	T const lengthSq() const
	{
		T sum = 0;
		for (int i = 0; i < Dimension; ++ i)
			sum += sq(Values[i]);
		return sum;
	}
	
	//! Distance between vectors
	T const getDistanceFrom(SVectorBase<T, Dimension> const & v) const
	{
		return (v - * this).length();
	}

	//! Normalize this vector
	void normalize()
	{
		T const len = length();
		
		for (int i = 0; i < Dimension; ++ i)
			Values[i] /= len;
	}

	//! Raw pointer access to vector values
	T const * const getValuePointer() const
	{
		return Values;
	}
	
	//! Raw pointer access to vector values
	T * const getValuePointer()
	{
		return Values;
	}

};

template <typename T, int Size, typename Implementation>
class SVector : public SVectorBase<T, Size>
{

private:
	
	SVector & operator = (SVector const &);

protected:

	SVector()
	{}

public:
	
	using SVectorBase<T, Dimension>::set;

	template <typename U>
	void set(IVectorBase<U> const & other)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] = (T) other[i];
	}

	T const dotProduct(SVectorBase<T, Dimension> const & other) const
	{
		T sum = 0;
		for (int i = 0; i < Dimension; ++ i)
			sum += this->Values[i] * other[i];
		return sum;
	}
	
	T const getDistanceFrom(SVectorBase<T, Dimension> const & v) const
	{
		return (v - * this).length();
	}
	
	Implementation const getInterpolated(SVectorBase<T, Dimension> const & v, T const d)
	{
		T inv = (T) 1.0 - d;
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = (T) v[i] * inv + this->Values[i] * d;
		return ret;
	}

	Implementation const getNormalized() const
	{
		Implementation ret = * this;
		ret.normalize();
		return ret;
	}
	
	template <typename otherImplementation>
	Implementation const operator + (SVector<T, Dimension, otherImplementation> const & v) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = this->Values[i] + (T) v[i];
		return ret;
	}
	
	template <typename otherImplementation>
	Implementation const operator - (SVector<T, Dimension, otherImplementation> const & v) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = this->Values[i] - (T) v[i];
		return ret;
	}
	
	template <typename otherImplementation>
	Implementation const operator * (SVector<T, Dimension, otherImplementation> const & v) const
	{
		
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = this->Values[i] * (T) v[i];
		return ret;
	}
	
	template <typename otherImplementation>
	Implementation const operator / (SVector<T, Dimension, otherImplementation> const & v) const
	{
		
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = this->Values[i] / (T) v[i];
		return ret;
	}

	Implementation const operator * (T const s) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = this->Values[i] * s;
		return ret;
	}

	Implementation const operator / (T const s) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = this->Values[i] / s;
		return ret;
	}

	friend Implementation const operator * (T const lhs, Self const & rhs) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = rhs.Values[i] * lhs;
		return ret;
	}

	friend Implementation const operator / (T const lhs, Self const & rhs) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = rhs.Values[i] / lhs;
		return ret;
	}

	template <typename otherImplementation>
	Self & operator += (SVector<T, Dimension, otherImplementation> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] += v[i];

		return * this;
	}
	
	template <typename otherImplementation>
	Self & operator -= (SVector<T, Dimension, otherImplementation> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] -= v[i];

		return * this;
	}

	template <typename otherImplementation>
	Self & operator *= (SVector<T, Dimension, otherImplementation> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] *= v[i];

		return * this;
	}

	template <typename otherImplementation>
	Self & operator /= (SVector<T, Dimension, otherImplementation> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] /= v[i];

		return * this;
	}

	Self & operator *= (T const s)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] *= s;

		return * this;
	}

	Self & operator /= (T const s)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] /= s;

		return * this;
	}

	template <typename otherImplementation>
	bool const operator <= (SVector<T, Dimension, otherImplementation> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (this->Values[i] <= v[i]);

		return result;
	}

	template <typename otherImplementation>
	bool const operator < (SVector<T, Dimension, otherImplementation> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (this->Values[i] < v[i]);

		return result;
	}

	template <typename otherImplementation>
	bool const operator >= (SVector<T, Dimension, otherImplementation> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (this->Values[i] >= v[i]);

		return result;
	}

	template <typename otherImplementation>
	bool const operator > (SVector<T, Dimension, otherImplementation> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (this->Values[i] > v[i]);

		return result;
	}

	template <typename otherImplementation>
	bool const operator == (SVector<T, Dimension, otherImplementation> const & v) const
	{
		return equals(v);
	}

	template <typename otherImplementation>
	bool const operator != (SVector<T, Dimension, otherImplementation> const & v) const
	{
		return ! equals(v);
	}

	template <typename otherImplementation>
	bool const equals(SVector<T, Dimension, otherImplementation> const & v, T const Epsilon = RoundingError<T>::Value()) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result &= ::equals(this->Values[i], v[i], Epsilon);

		return result;
	}

};

struct ForceReference
{};

#endif
