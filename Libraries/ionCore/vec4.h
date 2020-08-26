
#pragma once

#include "vec2.h"
#include "vec3.h"


namespace ion
{

	//! \brief 4D vector
	//! \ingroup ionCore
	template <typename T>
	class vec4
	{

	public:

		T X;
		T Y;
		T Z;
		T W;

		//////////////////
		// Constructors //
		//////////////////

		//! Default constructor
		vec4()
			: X(0), Y(0), Z(0), W(0)
		{}

		//! Scalar constructor
		vec4(T const in)
			: X(in), Y(in), Z(in), W(in)
		{}

		//! Explicit constructor
		vec4(T const x, T const y, T const z, T const w)
			: X(x), Y(y), Z(z), W(w)
		{}

		//! GLM constructor
		template <typename U>
		explicit vec4(glm::tvec4<U, glm::defaultp> const & v)
			: X(v.x), Y(v.y), Z(v.z), W(v.w)
		{}

		//! Generic constructor
		template <typename U>
		explicit vec4(vec4<U> const & vec)
			: X((T) vec.X), Y((T) vec.Y), Z((T) vec.Z), W((T) vec.W)
		{}

		//! vec3 constructor (vec3, w)
		vec4(vec3<T> const & vec, T const w = 0)
			: X(vec.X), Y(vec.Y), Z(vec.Z), W(w)
		{}

		//! vec3 constructor (x, vec3)
		vec4(T const x, vec3<T> const & vecYZW)
			: X(x), Y(vecYZW.X), Z(vecYZW.Y), W(vecYZW.Z)
		{}

		//! vec2 constructor (vec2, z, w)
		vec4(vec2<T> const & vec, T const z = 0, T const w = 0)
			: X(vec.X), Y(vec.Y), Z(z), W(w)
		{}

		//! vec2 constructor (x, vec2, w)
		vec4(T const x, vec2<T> const & vecYZ, T const w)
			: X(x), Y(vecYZ.X), Z(vecYZ.Y), W(w)
		{}

		//! vec2 constructor (x, y, vec2)
		vec4(T const x, T const y, vec2<T> const & vecZW)
			: X(x), Y(y), Z(vecZW.X), W(vecZW.Y)
		{}

		//! vec2 constructor (vec2, vec2)
		vec4(vec2<T> const & vecXY, vec2<T> const & vecZW)
			: X(vecXY.X), Y(vecXY.Y), Z(vecZW.X), W(vecZW.Y)
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
			case 3:
				return W;
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
			case 3:
				return W;
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
		vec4<T> & operator = (vec4<U> const & vec)
		{
			set(vec);
			return *this;
		}

		//! Sets all values to 0
		void reset()
		{
			X = Y = Z = W = 0;
		}

		//! Sets all values to a single scalar
		void set(T const in)
		{
			X = Y = Z = W = in;
		}

		//! Sets all values by an input C-style array
		void set(T const in[])
		{
			X = in[0];
			Y = in[1];
			Z = in[2];
			W = in[3];
		}

		//! Sets all values by an input vector
		template <typename U>
		void set(vec4<U> const & other)
		{
			X = (T) other.X;
			Y = (T) other.Y;
			Z = (T) other.Z;
			W = (T) other.W;
		}


		///////////////////////
		// Length Operations //
		///////////////////////

		//! Length of vector
		T Length() const
		{
			return Sqrt<T>(X*X + Y*Y + Z*Z + W*W);
		}

		//! Length of vector
		friend T Length(vec4<T> const & vec)
		{
			return vec.Length();
		}

		//! Squared-length of vector (computationally fast)
		T LengthSq() const
		{
			return X*X + Y*Y + Z*Z + W*W;
		}

		//! Squared-length of vector (computationally fast)
		friend T LengthSq(vec4<T> const & vec)
		{
			return vec.LengthSq();
		}


		/////////////////
		// Dot Product //
		/////////////////

		T Dot(vec4<T> const & other) const
		{
			return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
		}

		friend T Dot(vec4<T> const & lhs, vec4<T> const & rhs)
		{
			return lhs.Dot(rhs);
		}


		//////////////
		// Distance //
		//////////////

		T GetDistanceFrom(vec4<T> const & v) const
		{
			return (*this - v).Length();
		}

		friend T Distance(vec4<T> const & lhs, vec4<T> const & rhs)
		{
			return (lhs - rhs).Length();
		}

		T const GetDistanceSqFrom(vec4<T> const & v) const
		{
			return (* this - v).LengthSq();
		}

		friend T DistanceSq(vec4<T> const & lhs, vec4<T> const & rhs)
		{
			return (lhs - rhs).LengthSq();
		}


		///////////////////
		// Interpolation //
		///////////////////

		template <typename Real>
		vec4<T> GetInterpolated(vec4<T> const & v, Real const d) const
		{
			vec4<T> ret;
			Real inv = (Real) 1 - d;
			ret.X = (T) ((Real) v.X * inv + (Real) X * d);
			ret.Y = (T) ((Real) v.Y * inv + (Real) Y * d);
			ret.Z = (T) ((Real) v.Z * inv + (Real) Z * d);
			ret.W = (T) ((Real) v.W * inv + (Real) W * d);
			return ret;
		}

		template <typename Real>
		friend vec4<T> Interpolate(vec4<T> const & lhs, vec4<T> const & rhs, Real const d)
		{
			return lhs.GetInterpolated(rhs, d);
		}


		///////////////////
		// Normalization //
		///////////////////

		vec4<T> GetNormalized() const
		{
			vec4<T> ret = *this;
			ret.Normalize();
			return ret;
		}

		//! Normalize this vector
		vec4<T> & Normalize()
		{
			T const len = Length();

			X /= len;
			Y /= len;
			Z /= len;
			W /= len;

			return *this;
		}

		friend vec4<T> Normalize(vec4<T> const & v)
		{
			vec4<T> ret = v;
			ret.Normalize();
			return ret;
		}


		//////////////////////
		// Basic Arithmetic //
		//////////////////////

		vec4<T> operator + (vec4<T> const & v) const
		{
			vec4<T> ret;
			ret.X = X + v.X;
			ret.Y = Y + v.Y;
			ret.Z = Z + v.Z;
			ret.W = W + v.W;
			return ret;
		}

		vec4<T> operator - (vec4<T> const & v) const
		{
			vec3<T> ret;
			ret.X = X - v.X;
			ret.Y = Y - v.Y;
			ret.Z = Z - v.Z;
			ret.W = W - v.W;
			return ret;
		}

		vec4<T> operator * (vec4<T> const & v) const
		{
			vec4<T> ret;
			ret.X = X * v.X;
			ret.Y = Y * v.Y;
			ret.Z = Z * v.Z;
			ret.W = W * v.W;
			return ret;
		}

		vec4<T> operator / (vec4<T> const & v) const
		{
			vec4<T> ret;
			ret.X = X / v.X;
			ret.Y = Y / v.Y;
			ret.Z = Z / v.Z;
			ret.W = W / v.W;
			return ret;
		}


		///////////////////////
		// Scalar Arithmetic //
		///////////////////////

		vec4<T> operator + (T const s) const
		{
			vec4<T> ret;
			ret.X = X + s;
			ret.Y = Y + s;
			ret.Z = Z + s;
			ret.W = W + s;
			return ret;
		}

		vec4<T> operator - (T const s) const
		{
			vec4<T> ret;
			ret.X = X - s;
			ret.Y = Y - s;
			ret.Z = Z - s;
			ret.W = W - s;
			return ret;
		}

		vec4<T> operator * (T const s) const
		{
			vec4<T> ret;
			ret.X = X * s;
			ret.Y = Y * s;
			ret.Z = Z * s;
			ret.W = W * s;
			return ret;
		}

		vec4<T> operator / (T const s) const
		{
			vec4<T> ret;
			ret.X = X / s;
			ret.Y = Y / s;
			ret.Z = Z / s;
			ret.W = W / s;
			return ret;
		}

		friend vec4<T> operator + (T const lhs, vec4<T> const & rhs)
		{
			vec4<T> ret;
			ret.X = lhs + rhs.X;
			ret.Y = lhs + rhs.Y;
			ret.Z = lhs + rhs.Z;
			ret.W = lhs + rhs.W;
			return ret;
		}

		friend vec4<T> operator - (T const lhs, vec4<T> const & rhs)
		{
			vec4<T> ret;
			ret.X = lhs - rhs.X;
			ret.Y = lhs - rhs.Y;
			ret.Z = lhs - rhs.Z;
			ret.W = lhs - rhs.W;
			return ret;
		}

		friend vec4<T> operator * (T const lhs, vec4<T> const & rhs)
		{
			vec4<T> ret;
			ret.X = lhs * rhs.X;
			ret.Y = lhs * rhs.Y;
			ret.Z = lhs * rhs.Z;
			ret.W = lhs * rhs.W;
			return ret;
		}

		friend vec4<T> operator / (T const lhs, vec4<T> const & rhs)
		{
			vec4<T> ret;
			ret.X = lhs / rhs.X;
			ret.Y = lhs / rhs.Y;
			ret.Z = lhs / rhs.Z;
			ret.W = lhs / rhs.W;
			return ret;
		}


		/////////////////////////////////
		// Basic Arithmetic Assignment //
		/////////////////////////////////

		vec4<T> & operator += (vec4<T> const & v)
		{
			X += v.X;
			Y += v.Y;
			Z += v.Z;
			W += v.W;

			return * this;
		}

		vec4<T> & operator -= (vec4<T> const & v)
		{
			X -= v.X;
			Y -= v.Y;
			Z -= v.Z;
			W -= v.W;

			return * this;
		}

		vec4<T> & operator *= (vec4<T> const & v)
		{
			X *= v.X;
			Y *= v.Y;
			Z *= v.Z;
			W *= v.W;

			return * this;
		}

		vec4<T> & operator /= (vec4<T> const & v)
		{
			X /= v.X;
			Y /= v.Y;
			Z /= v.Z;
			W /= v.W;

			return * this;
		}


		//////////////////////////////////
		// Scalar Arithmetic Assignment //
		//////////////////////////////////

		vec4<T> & operator += (T const s)
		{
			X += s;
			Y += s;
			Z += s;
			W += s;

			return * this;
		}

		vec4<T> & operator -= (T const s)
		{
			X -= s;
			Y -= s;
			Z -= s;
			W -= s;

			return * this;
		}

		vec4<T> & operator *= (T const s)
		{
			X *= s;
			Y *= s;
			Z *= s;
			W *= s;

			return * this;
		}

		vec4<T> & operator /= (T const s)
		{
			X /= s;
			Y /= s;
			Z /= s;
			W /= s;

			return * this;
		}

		//////////////
		// Negation //
		//////////////

		vec4<T> const operator - () const
		{
			vec4<T> ret;
			ret.X = -X;
			ret.Y = -Y;
			ret.Z = -Z;
			ret.W = -W;
			return ret;
		}


		///////////////////////////////////////
		// Inequality operator (for sorting) //
		///////////////////////////////////////

		bool operator < (vec4<T> const & v) const
		{
			return
				(X < v.X) ||
				(X == v.X && Y < v.Y) ||
				(X == v.X && Y == v.Y && Z < v.Z) ||
				(X == v.X && Y == v.Y && Z == v.Z && W < v.W);
		}


		////////////////////////
		// Equality operators //
		////////////////////////

		bool operator == (vec4<T> const & v) const
		{
			return Equals(v);
		}

		bool operator != (vec4<T> const & v) const
		{
			return ! Equals(v);
		}

		bool Equals(vec4<T> const & v, T const Epsilon = RoundingError<T>::Value()) const
		{
			return
				ion::Equals(X, v.X, Epsilon) &&
				ion::Equals(Y, v.Y, Epsilon) &&
				ion::Equals(Z, v.Z, Epsilon) &&
				ion::Equals(W, v.W, Epsilon);
		}


		/////////////
		// Extrema //
		/////////////

		friend vec4<T> ComponentMinimum(vec4<T> const & lhs, vec4<T> const & rhs)
		{
			vec4<T> ret;
			ret.X = Minimum(lhs.X, rhs.X);
			ret.Y = Minimum(lhs.Y, rhs.Y);
			ret.Z = Minimum(lhs.Z, rhs.Z);
			ret.W = Minimum(lhs.W, rhs.W);
			return ret;
		}

		friend vec4<T> ComponentMaximum(vec4<T> const & lhs, vec4<T> const & rhs)
		{
			vec4<T> ret;
			ret.X = Maximum(lhs.X, rhs.X);
			ret.Y = Maximum(lhs.Y, rhs.Y);
			ret.Z = Maximum(lhs.Z, rhs.Z);
			ret.W = Maximum(lhs.W, rhs.W);
			return ret;
		}


		/////////
		// GLM //
		/////////

		glm::tvec4<T> const ToGLM() const
		{
			return glm::tvec4<T>(X, Y, Z, W);
		}

		static vec4<T> FromGLM(glm::tvec4<T> const & Vec)
		{
			return vec4<T>(Vec.x, Vec.y, Vec.z, Vec.w);
		}


		//////////////////////
		// Matrix Transform //
		//////////////////////

		void Transform(glm::mat4 const & mat)
		{
			glm::vec4 v = ToGLM();
			v = mat * v;
			*this = FromGLM(v);
		}

		vec4<T> GetTransformed(glm::mat4 const & mat) const
		{
			glm::vec4 v = ToGLM();
			v = mat * v;
			return FromGLM(v);
		}


		/////////////
		// Swizzle //
		/////////////

		vec2<T> XY() const
		{
			return vec2<T>(X, Y);
		}

		vec2<T> XZ() const
		{
			return vec2<T>(X, Z);
		}

		vec2<T> XW() const
		{
			return vec2<T>(X, W);
		}

		vec2<T> YZ() const
		{
			return vec2<T>(Y, Z);
		}

		vec2<T> ZW() const
		{
			return vec2<T>(Z, W);
		}

		vec3<T> XYZ() const
		{
			return vec3<T>(X, Y, Z);
		}

		T const * ValuePointer() const
		{
			if (&X + 1 == &Y && &Y + 1 == &Z && &Z + 1 == &W)
			{
				return &X;
			}
			else
			{
				static T Values[4];
				Values[0] = X;
				Values[1] = Y;
				Values[2] = Z;
				Values[3] = W;
				return Values;
			}
		}


		////////////////
		// Formatting //
		////////////////

		friend std::ostream & operator << (std::ostream & stream, vec4<T> const & vec)
		{
			return stream << +vec.X << " " << +vec.Y << " " << +vec.Z << " " << +vec.W;
		}

	};


	typedef vec4<float> vec4f;
	typedef vec4<double> vec4d;
	typedef vec4<int> vec4i;

}
