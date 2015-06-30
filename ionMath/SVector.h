
#pragma once

#include <ionCore.h>


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
	//! Note: Out-of-bounds access returns a dummy value without error
	virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < Dimension ? Values[i] : OutOfBounds = 0);
	}

	//! Member reference access
	//! Note: Out-of-bounds access returns a dummy value without error
	virtual T & operator[] (int i)
	{
		return (i >= 0 && i < Dimension ? Values[i] : OutOfBounds = 0);
	}

	//! Sets all values to 0
	void reset()
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = 0;
	}

	//! Sets all values to a single scalar
	void set(T const in)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = in;
	}

	//! Sets all values by an input C-style array
	void set(T const in[])
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = in[i];
	}

	//! Sets all values by an input vector
	template <typename U, u32 otherDimension>
	void set(SVectorBase<U, otherDimension> const & other)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = (T) other[i];
	}

	//! Length of vector
	T const Length() const
	{
		T sum = 0;
		for (u32 i = 0; i < Dimension; ++ i)
			sum += Sq(Values[i]);
		return (T) sqrt(sum);
	}

	//! Length of vector
	friend T const Length(SVectorBase<T, Dimension> const & vec)
	{
		return vec.Length();
	}

	//! Squared-length of vector (computationally fast)
	T const LengthSq() const
	{
		T sum = 0;
		for (u32 i = 0; i < Dimension; ++ i)
			sum += Sq(Values[i]);
		return sum;
	}

	//! Squared-length of vector (computationally fast)
	friend T const LengthSq(SVectorBase<T, Dimension> const & vec)
	{
		return vec.LengthSq();
	}

	//! Raw pointer access to vector values
	T const * GetValuePointer() const
	{
		return Values;
	}

	//! Raw pointer access to vector values
	T * GetValuePointer()
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
	typedef SVectorBase<T, Size> Other;

	Implementation & Clone()
	{
		return * static_cast<Implementation *>(this);
	}

	Implementation const & Clone() const
	{
		return * static_cast<Implementation const *>(this);
	}

protected:

	SVector()
	{}

public:

	using SVectorBase<T, Size>::Dimension;
	using SVectorBase<T, Dimension>::Values;
	using SVectorBase<T, Dimension>::set;
	using SVectorBase<T, Dimension>::Length;

	/////////////////
	// Dot Product //
	/////////////////

	T const DotProduct(Other const & other) const
	{
		T sum = 0;
		for (u32 i = 0; i < Dimension; ++ i)
			sum += Values[i] * other[i];
		return sum;
	}

	T const Dot(Other const & other) const
	{
		return DotProduct(other);
	}

	friend T const Dot(Type const & lhs, Other const & rhs)
	{
		return lhs.Dot(rhs);
	}

	//////////////
	// Distance //
	//////////////

	T const GetDistanceFrom(Other const & v) const
	{
		return (* this - v).Length();
	}

	friend T const Distance(Type const & lhs, Other const & rhs)
	{
		return (lhs - rhs).Length();
	}

	T const GetDistanceSqFrom(Other const & v) const
	{
		return (* this - v).LengthSq();
	}

	friend T const DistanceSq(Type const & lhs, Other const & rhs)
	{
		return (lhs - rhs).LengthSq();
	}

	///////////////////
	// Interpolation //
	///////////////////

	template <typename Real>
	Implementation const GetInterpolated(Other const & v, Real const d)
	{
		Real inv = (Real) 1 - d;
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = (T) ((Real) v[i] * inv + (Real) Values[i] * d);
		return ret;
	}

	template <typename Real>
	friend Implementation const Interpolate(Type const & lhs, Other const & rhs, Real const d)
	{
		return lhs.GetInterpolated(rhs, d);
	}

	///////////////////
	// Normalization //
	///////////////////

	Implementation const GetNormalized() const
	{
		Implementation ret = Clone();
		ret.Normalize();
		return ret;
	}

	//! Normalize this vector
	Type & Normalize()
	{
		T const len = Length();

		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] /= len;

		return * this;
	}

	friend Implementation const Normalize(Implementation const & v)
	{
		Implementation ret = v;
		ret.Normalize();
		return ret;
	}

	//////////////////////
	// Basic Arithmetic //
	//////////////////////

	Implementation const operator + (Other const & v) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] + v[i];
		return ret;
	}

	Implementation const operator - (Other const & v) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] - v[i];
		return ret;
	}

	Implementation const operator * (Other const & v) const
	{

		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] * v[i];
		return ret;
	}

	Implementation const operator / (Other const & v) const
	{

		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] / v[i];
		return ret;
	}

	///////////////////////
	// Scalar Arithmetic //
	///////////////////////

	Implementation const operator + (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] + s;
		return ret;
	}

	Implementation const operator - (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] - s;
		return ret;
	}

	Implementation const operator * (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] * s;
		return ret;
	}

	Implementation const operator / (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] / s;
		return ret;
	}

	friend Implementation const operator + (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs + rhs.Values[i];
		return ret;
	}

	friend Implementation const operator - (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs - rhs.Values[i];
		return ret;
	}

	friend Implementation const operator * (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs * rhs.Values[i];
		return ret;
	}

	friend Implementation const operator / (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs / rhs.Values[i];
		return ret;
	}

	/////////////////////////////////
	// Basic Arithmetic Assignment //
	/////////////////////////////////

	Type & operator += (Other const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] += v[i];

		return * this;
	}

	Type & operator -= (Other const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] -= v[i];

		return * this;
	}

	Type & operator *= (Other const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] *= v[i];

		return * this;
	}

	Type & operator /= (Other const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] /= v[i];

		return * this;
	}

	//////////////////////////////////
	// Scalar Arithmetic Assignment //
	//////////////////////////////////

	Type & operator += (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] += s;

		return * this;
	}

	Type & operator -= (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] -= s;

		return * this;
	}

	Type & operator *= (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] *= s;

		return * this;
	}

	Type & operator /= (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] /= s;

		return * this;
	}

	//////////////
	// Negation //
	//////////////

	Implementation const operator - () const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = - Values[i];
		return ret;
	}

	//////////////////////////
	// Comparison operators //
	//////////////////////////

	bool operator <= (Other const & v) const
	{
		for (int i = 0; i < Dimension; ++ i)
		{
			if (Values[i] < v.Values[i])
				return true;
			else if (Values[i] > v.Values[i])
				return false;
		}

		return true;
	}

	bool operator < (Other const & v) const
	{
		for (int i = 0; i < Dimension; ++ i)
		{
			if (Values[i] < v.Values[i])
				return true;
			else if (Values[i] > v.Values[i])
				return false;
		}

		return false;
	}

	bool operator >= (Other const & v) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result = result && (Values[i] >= v[i]);

		return result;
	}

	bool operator > (Other const & v) const
	{
		for (int i = 0; i < Dimension; ++ i)
		{
			if (Values[i] > v.Values[i])
				return true;
			else if (Values[i] < v.Values[i])
				return false;
		}

		return false;
	}

	////////////////////////
	// Equality operators //
	////////////////////////

	bool operator == (Other const & v) const
	{
		return Equals(v);
	}

	bool operator != (Other const & v) const
	{
		return ! Equals(v);
	}

	bool Equals(Other const & v, T const Epsilon = RoundingError<T>::Value()) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result &= ::Equals(Values[i], v[i], Epsilon);

		return result;
	}

	/////////////
	// Extrema //
	/////////////

	friend Implementation const ComponentMinimum(Type const & lhs, Other const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Minimum(lhs[i], rhs[i]);

		return ret;
	}

	friend Implementation const ComponentMaximum(Type const & lhs, Other const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Maximum(lhs[i], rhs[i]);

		return ret;
	}

};
