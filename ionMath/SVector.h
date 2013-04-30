#ifndef _ION_MATH_SVECTOR_H_INCLUDED_
#define _ION_MATH_SVECTOR_H_INCLUDED_

#include "ionConfig.h"

#include "ionUtils.h"

#include <cmath>


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
	void set(T const in)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] = in;
	}

	//! Sets all dimension values by an input C-style array
	void set(T const in[])
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
	T const * getValuePointer() const
	{
		return Values;
	}
	
	//! Raw pointer access to vector values
	T * getValuePointer()
	{
		return Values;
	}

};

template <typename T, int Size, typename Implementation>
class SVector : public SVectorBase<T, Size>
{

private:
	
	SVector & operator = (SVector const &);
	typedef SVector<T, Size, Implementation> Type;

protected:

	SVector()
	{}

public:
	
	using SVectorBase<T, Dimension>::set;

	template <typename U>
	void set(SVectorBase<U, Dimension> const & other)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] = (T) other[i];
	}

	T const dotProduct(SVectorBase<T, Dimension> const & other) const
	{
		T sum = 0;
		for (int i = 0; i < Dimension; ++ i)
			sum += Values[i] * other[i];
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
			ret[i] = (T) v[i] * inv + Values[i] * d;
		return ret;
	}

	Implementation const getNormalized() const
	{
		Implementation ret = * this;
		ret.normalize();
		return ret;
	}
	
	Implementation const operator + (SVectorBase<T, Dimension> const & v) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] + (T) v[i];
		return ret;
	}
	
	Implementation const operator - (SVectorBase<T, Dimension> const & v) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] - (T) v[i];
		return ret;
	}
	
	Implementation const operator * (SVectorBase<T, Dimension> const & v) const
	{
		
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] * (T) v[i];
		return ret;
	}
	
	Implementation const operator / (SVectorBase<T, Dimension> const & v) const
	{
		
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] / (T) v[i];
		return ret;
	}

	Implementation const operator * (T const s) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] * s;
		return ret;
	}

	Implementation const operator / (T const s) const
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] / s;
		return ret;
	}

	friend Implementation const operator * (T const lhs, Implementation const & rhs)
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = rhs.Values[i] * lhs;
		return ret;
	}

	friend Implementation const operator / (T const lhs, Implementation const & rhs)
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = rhs.Values[i] / lhs;
		return ret;
	}

	Implementation const operator - ()
	{
		Implementation ret;
		for (int i = 0; i < Dimension; ++ i)
			ret[i] = -Values[i];
		return ret;
	}

	Type & operator += (SVectorBase<T, Dimension> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] += v[i];

		return * this;
	}
	
	Type & operator -= (SVectorBase<T, Dimension> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] -= v[i];

		return * this;
	}

	Type & operator *= (SVectorBase<T, Dimension> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] *= v[i];

		return * this;
	}

	Type & operator /= (SVectorBase<T, Dimension> const & v)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] /= v[i];

		return * this;
	}

	Type & operator *= (T const s)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] *= s;

		return * this;
	}

	Type & operator /= (T const s)
	{
		for (int i = 0; i < Dimension; ++ i)
			Values[i] /= s;

		return * this;
	}

	bool operator <= (SVectorBase<T, Dimension> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (Values[i] <= v[i]);

		return result;
	}

	bool operator < (SVectorBase<T, Dimension> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (Values[i] < v[i]);

		return result;
	}

	bool operator >= (SVectorBase<T, Dimension> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (Values[i] >= v[i]);

		return result;
	}

	bool operator > (SVectorBase<T, Dimension> const & v) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result = result && (Values[i] > v[i]);

		return result;
	}

	bool operator == (SVectorBase<T, Dimension> const & v) const
	{
		return equals(v);
	}

	bool operator != (SVectorBase<T, Dimension> const & v) const
	{
		return ! equals(v);
	}

	bool equals(SVectorBase<T, Dimension> const & v, T const Epsilon = RoundingError<T>::Value()) const
	{
		bool result = true;
		for (int i = 0; i < Dimension; ++ i)
			result &= ::equals(Values[i], v[i], Epsilon);

		return result;
	}

};

struct ForceReference
{};

#endif
