
#pragma once

#include "ionTypes.h"
#include "ionComparison.h"

#include <glm/glm.hpp>


namespace ion
{

	//! \brief 2D vector
	//! \ingroup ionMath
	template <typename T>
	struct vec2
	{

		T X;
		T Y;

		//////////////////
		// Constructors //
		//////////////////

		//! Default constructor
		vec2()
			: X(0), Y(0)
		{}

		//! Scalar constructor
		vec2(T const in)
			: X(in), Y(in)
		{}

		//! Explicit constructor
		vec2(T const x, T const y)
			: X(x), Y(y)
		{}

		//! GLM constructor
		template <typename U>
		vec2(glm::tvec2<U, glm::defaultp> const & v)
			: X(v.x), Y(v.y)
		{}

		//! Generic vec2 constructor
		template <typename U>
		vec2(vec2<U> const & vec)
			: X((T) vec.X), Y((T) vec.Y)
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
		vec2<T> & operator = (vec2<U> const & vec)
		{
			set(vec);
			return *this;
		}

		//! Sets all values to 0
		void reset()
		{
			X = Y = 0;
		}

		//! Sets all values to a single scalar
		void set(T const in)
		{
			X = Y = in;
		}

		//! Sets all values by an input C-style array
		void set(T const in[])
		{
			X = in[0];
			Y = in[1];
		}

		//! Sets all values by an input vector
		template <typename U>
		void set(vec2<U> const & other)
		{
			X = (T) other.X;
			Y = (T) other.Y;
		}


		///////////////////////
		// Length Operations //
		///////////////////////

		//! Length of vector
		T Length() const
		{
			return Sqrt<T>(X*X + Y*Y);
		}

		//! Length of vector
		friend T Length(vec2<T> const & vec)
		{
			return vec.Length();
		}

		//! Squared-length of vector (computationally fast)
		T LengthSq() const
		{
			return X*X + Y*Y;
		}

		//! Squared-length of vector (computationally fast)
		friend T LengthSq(vec2<T> const & vec)
		{
			return vec.LengthSq();
		}


		/////////////////
		// Dot Product //
		/////////////////

		T Dot(vec2<T> const & other) const
		{
			return X * other.X + Y * other.Y;
		}

		friend T Dot(vec2<T> const & lhs, vec2<T> const & rhs)
		{
			return lhs.Dot(rhs);
		}


		//////////////
		// Distance //
		//////////////

		T GetDistanceFrom(vec2<T> const & v) const
		{
			return (*this - v).Length();
		}

		friend T Distance(vec2<T> const & lhs, vec2<T> const & rhs)
		{
			return (lhs - rhs).Length();
		}

		T const GetDistanceSqFrom(vec2<T> const & v) const
		{
			return (* this - v).LengthSq();
		}

		friend T DistanceSq(vec2<T> const & lhs, vec2<T> const & rhs)
		{
			return (lhs - rhs).LengthSq();
		}


		///////////////////
		// Interpolation //
		///////////////////

		template <typename Real>
		vec2<T> GetInterpolated(vec2<T> const & v, Real const d) const
		{
			vec2<T> ret;
			Real inv = (Real) 1 - d;
			ret.X = (T) ((Real) v.X * inv + (Real) X * d);
			ret.Y = (T) ((Real) v.Y * inv + (Real) Y * d);
			return ret;
		}

		template <typename Real>
		friend vec2<T> Interpolate(vec2<T> const & lhs, vec2<T> const & rhs, Real const d)
		{
			return lhs.GetInterpolated(rhs, d);
		}


		///////////////////
		// Normalization //
		///////////////////

		vec2<T> GetNormalized() const
		{
			vec2<T> ret = *this;
			ret.Normalize();
			return ret;
		}

		//! Normalize this vector
		vec2<T> & Normalize()
		{
			T const len = Length();

			X /= len;
			Y /= len;

			return *this;
		}

		friend vec2<T> Normalize(vec2<T> const & v)
		{
			vec2<T> ret = v;
			ret.Normalize();
			return ret;
		}


		//////////////////////
		// Basic Arithmetic //
		//////////////////////

		vec2<T> operator + (vec2<T> const & v) const
		{
			vec2<T> ret;
			ret.X = X + v.X;
			ret.Y = Y + v.Y;
			return ret;
		}

		vec2<T> operator - (vec2<T> const & v) const
		{
			vec2<T> ret;
			ret.X = X - v.X;
			ret.Y = Y - v.Y;
			return ret;
		}

		vec2<T> operator * (vec2<T> const & v) const
		{
			vec2<T> ret;
			ret.X = X * v.X;
			ret.Y = Y * v.Y;
			return ret;
		}

		vec2<T> operator / (vec2<T> const & v) const
		{
			vec2<T> ret;
			ret.X = X / v.X;
			ret.Y = Y / v.Y;
			return ret;
		}


		///////////////////////
		// Scalar Arithmetic //
		///////////////////////

		vec2<T> operator + (T const s) const
		{
			vec2<T> ret;
			ret.X = X + s;
			ret.Y = Y + s;
			return ret;
		}

		vec2<T> operator - (T const s) const
		{
			vec2<T> ret;
			ret.X = X - s;
			ret.Y = Y - s;
			return ret;
		}

		vec2<T> operator * (T const s) const
		{
			vec2<T> ret;
			ret.X = X * s;
			ret.Y = Y * s;
			return ret;
		}

		vec2<T> operator / (T const s) const
		{
			vec2<T> ret;
			ret.X = X / s;
			ret.Y = Y / s;
			return ret;
		}

		friend vec2<T> operator + (T const lhs, vec2<T> const & rhs)
		{
			vec2<T> ret;
			ret.X = lhs + rhs.X;
			ret.Y = lhs + rhs.Y;
			return ret;
		}

		friend vec2<T> operator - (T const lhs, vec2<T> const & rhs)
		{
			vec2<T> ret;
			ret.X = lhs - rhs.X;
			ret.Y = lhs - rhs.Y;
			return ret;
		}

		friend vec2<T> operator * (T const lhs, vec2<T> const & rhs)
		{
			vec2<T> ret;
			ret.X = lhs * rhs.X;
			ret.Y = lhs * rhs.Y;
			return ret;
		}

		friend vec2<T> operator / (T const lhs, vec2<T> const & rhs)
		{
			vec2<T> ret;
			ret.X = lhs / rhs.X;
			ret.Y = lhs / rhs.Y;
			return ret;
		}


		/////////////////////////////////
		// Basic Arithmetic Assignment //
		/////////////////////////////////

		vec2<T> & operator += (vec2<T> const & v)
		{
			X += v.X;
			Y += v.Y;

			return * this;
		}

		vec2<T> & operator -= (vec2<T> const & v)
		{
			X -= v.X;
			Y -= v.Y;

			return * this;
		}

		vec2<T> & operator *= (vec2<T> const & v)
		{
			X *= v.X;
			Y *= v.Y;

			return * this;
		}

		vec2<T> & operator /= (vec2<T> const & v)
		{
			X /= v.X;
			Y /= v.Y;

			return * this;
		}


		//////////////////////////////////
		// Scalar Arithmetic Assignment //
		//////////////////////////////////

		vec2<T> & operator += (T const s)
		{
			X += s;
			Y += s;

			return * this;
		}

		vec2<T> & operator -= (T const s)
		{
			X -= s;
			Y -= s;

			return * this;
		}

		vec2<T> & operator *= (T const s)
		{
			X *= s;
			Y *= s;

			return * this;
		}

		vec2<T> & operator /= (T const s)
		{
			X /= s;
			Y /= s;

			return * this;
		}

		//////////////
		// Negation //
		//////////////

		vec2<T> const operator - () const
		{
			vec2<T> ret;
			ret.X = -X;
			ret.Y = -Y;
			return ret;
		}


		///////////////////////////////////////
		// Inequality operator (for sorting) //
		///////////////////////////////////////

		bool operator < (vec2<T> const & v) const
		{
			return
				(X < v.X) ||
				(X == v.X && Y < v.Y);
		}


		////////////////////////
		// Equality operators //
		////////////////////////

		bool operator == (vec2<T> const & v) const
		{
			return Equals(v);
		}

		bool operator != (vec2<T> const & v) const
		{
			return ! Equals(v);
		}

		bool Equals(vec2<T> const & v, T const Epsilon = RoundingError<T>::Value()) const
		{
			return
				ion::Equals(X, v.X, Epsilon) &&
				ion::Equals(Y, v.Y, Epsilon);
		}


		/////////////
		// Extrema //
		/////////////

		friend vec2<T> ComponentMinimum(vec2<T> const & lhs, vec2<T> const & rhs)
		{
			vec2<T> ret;
			ret.X = Minimum(lhs.X, rhs.X);
			ret.Y = Minimum(lhs.Y, rhs.Y);
			return ret;
		}

		friend vec2<T> ComponentMaximum(vec2<T> const & lhs, vec2<T> const & rhs)
		{
			vec2<T> ret;
			ret.X = Maximum(lhs.X, rhs.X);
			ret.Y = Maximum(lhs.Y, rhs.Y);
			return ret;
		}


		/////////
		// GLM //
		/////////

		glm::vec2 const ToGLM() const
		{
			return glm::vec2(X, Y);
		}

		static vec2<T> FromGLM(glm::vec2 const & Vec)
		{
			return vec2<T>(Vec.x, Vec.y);
		}


		/////////////
		// Swizzle //
		/////////////

		vec2<T> YX() const
		{
			return vec2<T>(Y, X);
		}

		vec2<T> XX() const
		{
			return vec2<T>(X, X);
		}

		vec2<T> YY() const
		{
			return vec2<T>(Y, Y);
		}


		////////////////
		// Formatting //
		////////////////

		friend std::ostream & operator << (std::ostream & stream, vec2<T> const & vec)
		{
			return stream << vec.X << " " << vec.Y;
		}


		//////////////
		// Rotation //
		//////////////

		vec2<T> Rotate(T const radians) const
		{
			vec2<T> Ret;
			T C = Cos(radians);
			T S = Sin(radians);
			Ret.X = X * C - Y * S;
			Ret.Y = X * S + Y * C;
			return Ret;
		}

		T GetAngle() const
		{
			return ArcTan(Y, X);
		}

	};

	typedef vec2<float> vec2f;
	typedef vec2<double> vec2d;
	typedef vec2<int> vec2i;
	typedef vec2<ion::uint> vec2u;

}