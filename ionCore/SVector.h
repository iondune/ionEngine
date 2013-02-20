#ifndef _ION_CORE_SVECTOR_H_INCLUDED_
#define _ION_CORE_SVECTOR_H_INCLUDED_

#include <cmath>

#include "ionUtils.h"

template <typename T, u32 Size>
class SVectorSimple
{

private:
	
	SVectorSimple & operator = (SVectorSimple const &);

protected:

	SVectorSimple()
	{}

public:

	static u32 const Dimension = Size;
	T Values[Dimension];
	mutable T OutOfBounds;

	virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < Dimension ? this->Values[i] : OutOfBounds = 0);
	}

	virtual T & operator[] (int i)
	{
		return (i >= 0 && i < Dimension ? this->Values[i] : OutOfBounds = 0);
	}

	void reset()
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] = 0;
	}

	void set(T const in)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] = in;
	}

	void set(T const in[])
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] = in[i];
	}

	T const length() const
	{
		T sum = 0;
		for (int i = 0; i < Dimension; ++ i)
			sum += sq(this->Values[i]);
		return (T) sqrt(sum);
	}
	
	T const getDistanceFrom(SVectorSimple<T, Dimension> const & v) const
	{
		return (v - * this).length();
	}

	void normalize()
	{
		T const len = length();
		
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] /= len;
	}

	T const * const getValuePointer() const
	{
		return this->Values;
	}

	T * const getValuePointer()
	{
		return this->Values;
	}

};

template <typename T, int Dimension, typename Implementation>
class SVector : public SVectorSimple<T, Dimension>
{

private:
	
	SVector & operator = (SVector const &);

	typedef SVector<T, Dimension, Implementation> Self;

protected:

	SVector()
	{}

public:
	
	void set(T const in)
	{
		SVectorSimple<T, Dimension>::set(in);
	}

	void set(T const in[])
	{
		SVectorSimple<T, Dimension>::set(in);
	}

	template <typename U, int otherDimension, typename otherImplementation>
	void set(SVector<U, otherDimension, otherImplementation> const & other)
	{
		for (int i = 0; i < Dimension; ++ i)
			this->Values[i] = (T) other[i];
	}

	template <typename otherImplementation>
	T const dotProduct(SVector<T, Dimension, otherImplementation> const & other) const
	{
		T sum = 0;
		for (int i = 0; i < Dimension; ++ i)
			sum += this->Values[i] * other[i];
		return sum;
	}
	
	template <typename otherImplementation>
	T const getDistanceFrom(SVector<T, Dimension, otherImplementation> const & v) const
	{
		return (v - * this).length();
	}
	
	template <typename otherImplementation>
	Implementation const getInterpolated(SVector<T, Dimension, otherImplementation> const & v, T const d)
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
