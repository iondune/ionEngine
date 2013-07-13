#pragma once

#include "ionConfig.h"
#include "ionUtils.h"


template <typename T, u32 Size>
class SVectorBase
{

private:
	
	SVectorBase & operator = (SVectorBase const &);

protected:

	ION_FUNC_DEF SVectorBase()
	{}

public:

	static u32 const Dimension = Size;
	T Values[Dimension];
	mutable T OutOfBounds;
	
	//! Const member copy access
	//! Note: Out-of-bounds access returns a dummy value without error
	ION_FUNC_DEF virtual T const operator[] (int i) const
	{
		return (i >= 0 && i < Dimension ? Values[i] : OutOfBounds = 0);
	}
	
	//! Member reference access
	//! Note: Out-of-bounds access returns a dummy value without error
	ION_FUNC_DEF virtual T & operator[] (int i)
	{
		return (i >= 0 && i < Dimension ? Values[i] : OutOfBounds = 0);
	}

	//! Sets all values to 0
	ION_FUNC_DEF void reset()
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = 0;
	}

	//! Sets all values to a single scalar
	ION_FUNC_DEF void set(T const in)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = in;
	}

	//! Sets all values by an input C-style array
	ION_FUNC_DEF void set(T const in[])
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = in[i];
	}
	
	//! Sets all values by an input vector
	template <typename U, u32 otherDimension>
	ION_FUNC_DEF void set(SVectorBase<U, otherDimension> const & other)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] = (T) other[i];
	}
	
	//! Length of vector
	ION_FUNC_DEF T const Length() const
	{
		T sum = 0;
		for (u32 i = 0; i < Dimension; ++ i)
			sum += Sq(Values[i]);
		return (T) sqrt(sum);
	}

	//! Length of vector
	ION_FUNC_DEF friend T const Length(SVectorBase<T, Dimension> const & vec)
	{
		return vec.Length();
	}

	//! Squared-length of vector (computationally fast)
	ION_FUNC_DEF T const LengthSq() const
	{
		T sum = 0;
		for (u32 i = 0; i < Dimension; ++ i)
			sum += Sq(Values[i]);
		return sum;
	}

	//! Squared-length of vector (computationally fast)
	ION_FUNC_DEF friend T const LengthSq(SVectorBase<T, Dimension> const & vec)
	{
		return vec.LengthSq();
	}

	//! Normalize this vector
	ION_FUNC_DEF void Normalize()
	{
		T const len = Length();
		
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] /= len;
	}

	//! Raw pointer access to vector values
	ION_FUNC_DEF T const * GetValuePointer() const
	{
		return Values;
	}
	
	//! Raw pointer access to vector values
	ION_FUNC_DEF T * GetValuePointer()
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

protected:

	ION_FUNC_DEF SVector()
	{}

public:
	
	using SVectorBase<T, Dimension>::set;

	/////////////////
	// Dot Product //
	/////////////////
	
	ION_FUNC_DEF T const DotProduct(Other const & other) const
	{
		T sum = 0;
		for (u32 i = 0; i < Dimension; ++ i)
			sum += Values[i] * other[i];
		return sum;
	}

	ION_FUNC_DEF T const Dot(Other const & other) const
	{
		return DotProduct(other);
	}

	ION_FUNC_DEF friend T const Dot(Type const & lhs, Other const & rhs)
	{
		return lhs.Dot(rhs);
	}

	//////////////
	// Distance //
	//////////////

	ION_FUNC_DEF T const GetDistanceFrom(Other const & v) const
	{
		return (* this - v).length();
	}
	
	ION_FUNC_DEF friend T const Distance(Type const & lhs, Other const & rhs)
	{
		return (lhs - rhs).length();
	}
	
	ION_FUNC_DEF T const GetDistanceSqFrom(Other const & v) const
	{
		return (* this - v).lengthSq();
	}
	
	ION_FUNC_DEF friend T const DistanceSq(Type const & lhs, Other const & rhs)
	{
		return (lhs - rhs).lengthSq();
	}
	
	///////////////////
	// Interpolation //
	///////////////////
	
	template <typename Real>
	ION_FUNC_DEF Implementation const GetInterpolated(Other const & v, Real const d)
	{
		Real inv = (Real) 1 - d;
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = (T) ((Real) v[i] * inv + (Real) Values[i] * d);
		return ret;
	}
	
	template <typename Real>
	ION_FUNC_DEF friend Implementation const Interpolate(Type const & lhs, Other const & rhs, Real const d)
	{
		return lhs.GetInterpolated(rhs, d);
	}

	///////////////////
	// Normalization //
	///////////////////

	ION_FUNC_DEF Implementation const GetNormalized() const
	{
		Implementation ret = * this;
		ret.Normalize();
		return ret;
	}

	friend ION_FUNC_DEF Implementation const Normalize(Implementation const & v)
	{
		Implementation ret = v;
		ret.normalize();
		return ret;
	}

	//////////////////////
	// Basic Arithmetic //
	//////////////////////
	
	ION_FUNC_DEF Implementation const operator + (Other const & v) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] + v[i];
		return ret;
	}
	
	ION_FUNC_DEF Implementation const operator - (Other const & v) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] - v[i];
		return ret;
	}
	
	ION_FUNC_DEF Implementation const operator * (Other const & v) const
	{
		
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] * v[i];
		return ret;
	}
	
	ION_FUNC_DEF Implementation const operator / (Other const & v) const
	{
		
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] / v[i];
		return ret;
	}

	///////////////////////
	// Scalar Arithmetic //
	///////////////////////
	
	ION_FUNC_DEF Implementation const operator + (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] + s;
		return ret;
	}
	
	ION_FUNC_DEF Implementation const operator - (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] - s;
		return ret;
	}

	ION_FUNC_DEF Implementation const operator * (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] * s;
		return ret;
	}

	ION_FUNC_DEF Implementation const operator / (T const s) const
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Values[i] / s;
		return ret;
	}

	ION_FUNC_DEF friend Implementation const operator + (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs + rhs.Values[i];
		return ret;
	}

	ION_FUNC_DEF friend Implementation const operator - (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs - rhs.Values[i];
		return ret;
	}

	ION_FUNC_DEF friend Implementation const operator * (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs * rhs.Values[i];
		return ret;
	}

	ION_FUNC_DEF friend Implementation const operator / (T const lhs, Type const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = lhs / rhs.Values[i];
		return ret;
	}

	/////////////////////////////////
	// Basic Arithmetic Assignment //
	/////////////////////////////////

	ION_FUNC_DEF Type & operator += (SVectorBase<T, Dimension> const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] += v[i];

		return * this;
	}
	
	ION_FUNC_DEF Type & operator -= (SVectorBase<T, Dimension> const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] -= v[i];

		return * this;
	}

	ION_FUNC_DEF Type & operator *= (SVectorBase<T, Dimension> const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] *= v[i];

		return * this;
	}

	ION_FUNC_DEF Type & operator /= (SVectorBase<T, Dimension> const & v)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] /= v[i];

		return * this;
	}

	//////////////////////////////////
	// Scalar Arithmetic Assignment //
	//////////////////////////////////

	ION_FUNC_DEF Type & operator += (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] += s;

		return * this;
	}

	ION_FUNC_DEF Type & operator -= (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] -= s;

		return * this;
	}

	ION_FUNC_DEF Type & operator *= (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] *= s;

		return * this;
	}

	ION_FUNC_DEF Type & operator /= (T const s)
	{
		for (u32 i = 0; i < Dimension; ++ i)
			Values[i] /= s;

		return * this;
	}

	//////////////
	// Negation //
	//////////////

	ION_FUNC_DEF Implementation const operator - ()
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = - Values[i];
		return ret;
	}
	
	//////////////////////////
	// Comparison operators //
	//////////////////////////

	ION_FUNC_DEF bool operator <= (Other const & v) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result = result && (Values[i] <= v[i]);

		return result;
	}

	ION_FUNC_DEF bool operator < (Other const & v) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result = result && (Values[i] < v[i]);

		return result;
	}

	ION_FUNC_DEF bool operator >= (Other const & v) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result = result && (Values[i] >= v[i]);

		return result;
	}

	ION_FUNC_DEF bool operator > (Other const & v) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result = result && (Values[i] > v[i]);

		return result;
	}

	////////////////////////
	// Equality operators //
	////////////////////////

	ION_FUNC_DEF bool operator == (Other const & v) const
	{
		return Equals(v);
	}

	ION_FUNC_DEF bool operator != (Other const & v) const
	{
		return ! Equals(v);
	}

	template <typename Real>
	ION_FUNC_DEF bool Equals(Other const & v, Real const Epsilon = RoundingError<Real>::Value()) const
	{
		bool result = true;
		for (u32 i = 0; i < Dimension; ++ i)
			result &= ::Equals(Values[i], v[i], Epsilon);

		return result;
	}

	/////////////
	// Extrema //
	/////////////

	ION_FUNC_DEF friend Implementation const Minimum(Type const & lhs, Other const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Minimum(lhs[i], rhs[i]);

		return ret;
	}

	ION_FUNC_DEF friend Implementation const Maximum(Type const & lhs, Other const & rhs)
	{
		Implementation ret;
		for (u32 i = 0; i < Dimension; ++ i)
			ret[i] = Maximum(lhs[i], rhs[i]);

		return ret;
	}

};
