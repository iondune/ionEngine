
#pragma once

#include <ionConfig.h>

#include "SVector2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//! \brief 3D vector
//! \ingroup ionMath
template <typename T>
struct vec3
{

	T X;
	T Y;
	T Z;

	//////////////////
	// Constructors //
	//////////////////

	//! Default constructor
	vec3()
		: X(0), Y(0), Z(0)
	{}

	//! Scalar constructor
	vec3(T const in)
		: X(in), Y(in), Z(in)
	{}

	//! Explicit constructor
	vec3(T const x, T const y, T const z)
		: X(x), Y(y), Z(z)
	{}

	//! GLM constructor
	template <typename U>
	vec3(glm::tvec3<U, glm::defaultp> const & v)
		: X(v.x), Y(v.y), Z(v.z)
	{}

	//! Generic vec3 constructor
	template <typename U>
	vec3(vec3<U> const & vec)
		: X((T) vec.X), Y((T) vec.Y), Z((T) vec.Z)
	{}

	//! Generic vec2 constructor
	template <typename U>
	vec3(vec2<U> const & vec)
		: X((T) vec.X), Y((T) vec.Y), Z(0)
	{}

	
	/////////////////////
	// Index Operators //
	/////////////////////

	//! Note: Out-of-bounds access returns a dummy value without error
	T operator[] (int i) const
	{
		switch (i)
		{
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		default:
			return 0;
		}
	}

	//! Note: Out-of-bounds access returns a dummy value without error
	T & operator[] (int i)
	{
		switch (i)
		{
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		default:
		{
			static T Dummy;
			return Dummy = 0;
		}
		}
	}


	////////////////
	// Assignment //
	////////////////
		
	//! Generic vector assignment operator
	template <typename U>
	vec3<T> & operator = (vec3<U> const & vec)
	{
		set(vec);
		return *this;
	}

	//! Sets all values to 0
	void reset()
	{
		X = Y = Z = 0;
	}

	//! Sets all values to a single scalar
	void set(T const in)
	{
		X = Y = Z = in;
	}

	//! Sets all values by an input C-style array
	void set(T const in[])
	{
		X = in[0];
		Y = in[1];
		Z = in[2];
	}

	//! Sets all values by an input vector
	template <typename U>
	void set(vec3<U> const & other)
	{
		X = (T) other.X;
		Y = (T) other.Y;
		Z = (T) other.Z;
	}


	///////////////////////
	// Length Operations //
	///////////////////////

	//! Length of vector
	T Length() const
	{
		return Sqrt<T>(X*X + Y*Y + Z*Z);
	}

	//! Length of vector
	friend T Length(vec3<T> const & vec)
	{
		return vec.Length();
	}

	//! Squared-length of vector (computationally fast)
	T LengthSq() const
	{
		return X*X + Y*Y + Z*Z;
	}

	//! Squared-length of vector (computationally fast)
	friend T LengthSq(vec3<T> const & vec)
	{
		return vec.LengthSq();
	}


	/////////////////
	// Dot Product //
	/////////////////

	T Dot(vec3<T> const & other) const
	{
		return X * other.X + Y * other.Y + Z * other.Z;
	}

	friend T Dot(vec3<T> const & lhs, vec3<T> const & rhs)
	{
		return lhs.Dot(rhs);
	}


	//////////////
	// Distance //
	//////////////

	T GetDistanceFrom(vec3<T> const & v) const
	{
		return (*this - v).Length();
	}

	friend T Distance(vec3<T> const & lhs, vec3<T> const & rhs)
	{
		return (lhs - rhs).Length();
	}

	T const GetDistanceSqFrom(vec3<T> const & v) const
	{
		return (* this - v).LengthSq();
	}

	friend T DistanceSq(vec3<T> const & lhs, vec3<T> const & rhs)
	{
		return (lhs - rhs).LengthSq();
	}


	///////////////////
	// Interpolation //
	///////////////////

	template <typename Real>
	vec3<T> GetInterpolated(vec3<T> const & v, Real const d) const
	{
		vec3<T> ret;
		Real inv = (Real) 1 - d;
		ret.X = (T) ((Real) v.X * inv + (Real) X * d);
		ret.Y = (T) ((Real) v.Y * inv + (Real) Y * d);
		ret.Z = (T) ((Real) v.Z * inv + (Real) Z * d);
		return ret;
	}

	template <typename Real>
	friend vec3<T> Interpolate(vec3<T> const & lhs, vec3<T> const & rhs, Real const d)
	{
		return lhs.GetInterpolated(rhs, d);
	}


	///////////////////
	// Normalization //
	///////////////////

	vec3<T> GetNormalized() const
	{
		vec3<T> ret = *this;
		ret.Normalize();
		return ret;
	}

	//! Normalize this vector
	vec3<T> & Normalize()
	{
		T const len = Length();

		X /= len;
		Y /= len;
		Z /= len;

		return *this;
	}

	friend vec3<T> Normalize(vec3<T> const & v)
	{
		vec3<T> ret = v;
		ret.Normalize();
		return ret;
	}


	//////////////////////
	// Basic Arithmetic //
	//////////////////////

	vec3<T> operator + (vec3<T> const & v) const
	{
		vec3<T> ret;
		ret.X = X + v.X;
		ret.Y = Y + v.Y;
		ret.Z = Z + v.Z;
		return ret;
	}

	vec3<T> operator - (vec3<T> const & v) const
	{
		vec3<T> ret;
		ret.X = X - v.X;
		ret.Y = Y - v.Y;
		ret.Z = Z - v.Z;
		return ret;
	}

	vec3<T> operator * (vec3<T> const & v) const
	{
		vec3<T> ret;
		ret.X = X * v.X;
		ret.Y = Y * v.Y;
		ret.Z = Z * v.Z;
		return ret;
	}

	vec3<T> operator / (vec3<T> const & v) const
	{
		vec3<T> ret;
		ret.X = X / v.X;
		ret.Y = Y / v.Y;
		ret.Z = Z / v.Z;
		return ret;
	}


	///////////////////////
	// Scalar Arithmetic //
	///////////////////////

	vec3<T> operator + (T const s) const
	{
		vec3<T> ret;
		ret.X = X + s;
		ret.Y = Y + s;
		ret.Z = Z + s;
		return ret;
	}

	vec3<T> operator - (T const s) const
	{
		vec3<T> ret;
		ret.X = X - s;
		ret.Y = Y - s;
		ret.Z = Z - s;
		return ret;
	}

	vec3<T> operator * (T const s) const
	{
		vec3<T> ret;
		ret.X = X * s;
		ret.Y = Y * s;
		ret.Z = Z * s;
		return ret;
	}

	vec3<T> operator / (T const s) const
	{
		vec3<T> ret;
		ret.X = X / s;
		ret.Y = Y / s;
		ret.Z = Z / s;
		return ret;
	}

	friend vec3<T> operator + (T const lhs, vec3<T> const & rhs)
	{
		vec3<T> ret;
		ret.X = lhs + rhs.X;
		ret.Y = lhs + rhs.Y;
		ret.Z = lhs + rhs.Z;
		return ret;
	}

	friend vec3<T> operator - (T const lhs, vec3<T> const & rhs)
	{
		vec3<T> ret;
		ret.X = lhs - rhs.X;
		ret.Y = lhs - rhs.Y;
		ret.Z = lhs - rhs.Z;
		return ret;
	}

	friend vec3<T> operator * (T const lhs, vec3<T> const & rhs)
	{
		vec3<T> ret;
		ret.X = lhs * rhs.X;
		ret.Y = lhs * rhs.Y;
		ret.Z = lhs * rhs.Z;
		return ret;
	}

	friend vec3<T> operator / (T const lhs, vec3<T> const & rhs)
	{
		vec3<T> ret;
		ret.X = lhs / rhs.X;
		ret.Y = lhs / rhs.Y;
		ret.Z = lhs / rhs.Z;
		return ret;
	}


	/////////////////////////////////
	// Basic Arithmetic Assignment //
	/////////////////////////////////

	vec3<T> & operator += (vec3<T> const & v)
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;

		return * this;
	}

	vec3<T> & operator -= (vec3<T> const & v)
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;

		return * this;
	}

	vec3<T> & operator *= (vec3<T> const & v)
	{
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;

		return * this;
	}

	vec3<T> & operator /= (vec3<T> const & v)
	{
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;

		return * this;
	}


	//////////////////////////////////
	// Scalar Arithmetic Assignment //
	//////////////////////////////////

	vec3<T> & operator += (T const s)
	{
		X += s;
		Y += s;
		Z += s;

		return * this;
	}

	vec3<T> & operator -= (T const s)
	{
		X -= s;
		Y -= s;
		Z -= s;

		return * this;
	}

	vec3<T> & operator *= (T const s)
	{
		X *= s;
		Y *= s;
		Z *= s;

		return * this;
	}

	vec3<T> & operator /= (T const s)
	{
		X /= s;
		Y /= s;
		Z /= s;

		return * this;
	}

	//////////////
	// Negation //
	//////////////

	vec3<T> const operator - () const
	{
		vec3<T> ret;
		ret.X = -X;
		ret.Y = -Y;
		ret.Z = -Z;
		return ret;
	}


	///////////////////////////////////////
	// Inequality operator (for sorting) //
	///////////////////////////////////////

	bool operator < (vec3<T> const & v) const
	{
		return 
			(X < v.X) ||
			(X == v.X && Y < v.Y) ||
			(X == v.X && Y == v.Y && Z < v.Z);
	}


	////////////////////////
	// Equality operators //
	////////////////////////

	bool operator == (vec3<T> const & v) const
	{
		return Equals(v);
	}

	bool operator != (vec3<T> const & v) const
	{
		return ! Equals(v);
	}

	bool Equals(vec3<T> const & v, T const Epsilon = ion::RoundingError<T>::Value()) const
	{
		return
			::Equals(X, v.X, Epsilon) &&
			::Equals(Y, v.Y, Epsilon) &&
			::Equals(Z, v.Z, Epsilon);
	}


	/////////////
	// Extrema //
	/////////////

	friend vec3<T> ComponentMinimum(vec3<T> const & lhs, vec3<T> const & rhs)
	{
		vec3<T> ret;
		ret.X = Minimum(lhs.X, rhs.X);
		ret.Y = Minimum(lhs.Y, rhs.Y);
		ret.Z = Minimum(lhs.Z, rhs.Z);
		return ret;
	}

	friend vec3<T> ComponentMaximum(vec3<T> const & lhs, vec3<T> const & rhs)
	{
		vec3<T> ret;
		ret.X = Maximum(lhs.X, rhs.X);
		ret.Y = Maximum(lhs.Y, rhs.Y);
		ret.Z = Maximum(lhs.Z, rhs.Z);
		return ret;
	}


	///////////////////
	// Cross Product //
	///////////////////

	//! Vector cross product
	vec3<T> CrossProduct(vec3<T> const & v) const
	{
		return vec3<T>(Y*v.Z - v.Y*Z, v.X*Z - X*v.Z, X*v.Y - v.X*Y);
	}

	//! Vector cross product
	vec3<T> Cross(vec3<T> const & v) const
	{
		return vec3<T>(Y*v.Z - v.Y*Z, v.X*Z - X*v.Z, X*v.Y - v.X*Y);
	}

	//! Vector cross product
	friend vec3<T> Cross(vec3<T> const & lhs, vec3<T> const & rhs)
	{
		return lhs.Cross(rhs);
	}


	/////////
	// GLM //
	/////////

	glm::vec3 const ToGLM() const
	{
		return glm::vec3(X, Y, Z);
	}

	static vec3<T> FromGLM(glm::vec3 const & Vec)
	{
		return vec3<T>(Vec.x, Vec.y, Vec.z);
	}

	static vec3<T> FromGLM(glm::vec4 const & Vec)
	{
		return vec3<T>(Vec.x, Vec.y, Vec.z);
	}


	//////////////////////
	// Matrix Transform //
	//////////////////////

	void Transform(glm::mat4 const & mat, float const TranslateComponent = 1)
	{
		glm::vec4 v = glm::vec4(ToGLM(), TranslateComponent);
		v = mat * v;
		*this = FromGLM(v);
	}

	vec3<T> GetTransformed(glm::mat4 const & mat, float const TranslateComponent = 1) const
	{
		glm::vec4 v = glm::vec4(ToGLM(), TranslateComponent);
		v = mat * v;
		return FromGLM(v);
	}

	vec3<T> RotateAround(vec3<T> const & other, float const radians) const
	{
		return GetTransformed(glm::rotate(glm::mat4(1.f), radians, other.ToGLM()));
	}


	/////////////
	// Swizzle //
	/////////////

	vec2<T> XY() const
	{
		return vec2<T>(X, Y);
	}

	vec2<T> YZ() const
	{
		return vec2<T>(Y, Z);
	}

	vec2<T> XZ() const
	{
		return vec2<T>(X, Z);
	}


	////////////////
	// Formatting //
	////////////////

	friend std::ostream & operator << (std::ostream & stream, vec3<T> const & vec)
	{
		return stream << +vec.X << " " << +vec.Y << " " << +vec.Z;
	}

};

typedef vec3<float> vec3f;
typedef vec3<double> vec3d;
typedef vec3<int> vec3i;
typedef vec3<ion::uint> vec3u;
