#ifndef _CABBAGE_CORE_SVECTOR3_H_INCLUDED_
#define _CABBAGE_CORE_SVECTOR3_H_INCLUDED_

#include <cmath>

#include <glm/glm.hpp>

#include "ionUtils.h"
#include "SVector2.h"

template <typename T>
class SVector3;

template <typename T>
class SVector3Reference
{

	SVector3Reference();
	SVector3Reference & operator = (SVector3Reference const &);

public:

	T & X, & Y, & Z;

	SVector3Reference(float & x, float & y, float & z)
		: X(x), Y(y), Z(z)
	{}

	SVector3Reference(SVector3Reference const & v)
		: X(v.X), Y(v.Y), Z(v.Z)
	{}

	glm::vec3 const getGLMVector() const
	{
		return glm::vec3(X, Y, Z);
	}

	T const operator[] (unsigned int i) const
	{
		switch (i)
		{
		default:
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		}
	}

	T & operator[] (unsigned int i)
	{
		switch (i)
		{
		default:
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
		}
	}

	SVector3<T> crossProduct(SVector3Reference const & v) const;

	SVector3<T> const getNormalized() const;

	SVector3<T> operator + (SVector3<T> const & v) const;

	SVector3<T> operator - (SVector3<T> const & v) const;

	SVector3<T> operator * (SVector3<T> const & v) const;

	SVector3<T> operator / (SVector3<T> const & v) const;

	SVector3<T> operator * (T const s) const;

	SVector3<T> operator / (T const s) const;

	T dotProduct(SVector3Reference const & v) const
	{
		return X*v.X + Y*v.Y + Z*v.Z;
	}

	void normalize()
	{
		float const len = length();

		X /= len;
		Y /= len;
		Z /= len;
	}

	T length() const
	{
		return sqrtf(X*X + Y*Y + Z*Z);
	}

	SVector3Reference & operator += (SVector3Reference const & v)
	{
		X += v.X;
		Y += v.Y;
		Z += v.Z;

		return * this;
	}

	SVector3Reference & operator -= (SVector3Reference const & v)
	{
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;

		return * this;
	}

	SVector3Reference & operator *= (SVector3Reference const & v)
	{
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;

		return * this;
	}

	SVector3Reference & operator /= (SVector3Reference const & v)
	{
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;

		return * this;
	}

	SVector3Reference & operator *= (float const s)
	{
		X *= s;
		Y *= s;
		Z *= s;

		return * this;
	}

	SVector3Reference & operator /= (float const s)
	{
		X /= s;
		Y /= s;
		Z /= s;

		return * this;
	}

	bool const operator <= (SVector3Reference const & v) const
	{
		return (X < v.X && Y < v.Y && Z < v.Z);
	}

	bool const operator >= (SVector3Reference const & v) const
	{
		return (X > v.X && Y > v.Y && Z > v.Z);
	}

	bool const operator == (SVector3Reference const & v) const
	{
		return equals(v);
	}

	bool const operator != (SVector3Reference const & v) const
	{
		return ! equals(v);
	}

	bool const equals(SVector3Reference const & v, float const Epsilon = RoundingError32) const
	{
		return ::equals(X, v.X, Epsilon) && ::equals(Y, v.Y, Epsilon) && ::equals(Z, v.Z, Epsilon);
	}

	SVector2Reference<T> const xy()
	{
		return SVector2Reference<T>(X, Y);
	}

	SVector2Reference<T> const xz()
	{
		return SVector2Reference<T>(X, Z);
	}

	SVector2Reference<T> const yz()
	{
		return SVector2Reference<T>(Y, Z);
	}

};

template <typename T>
class SVector3 : public SVector3Reference<T>
{

public:

	T X, Y, Z;

	SVector3()
		: X(0), Y(0), Z(0), SVector3Reference<T>(X, Y, Z)
	{}

	template <typename U>
	SVector3(SVector3Reference<U> const & vec)
		: X(vec.X), Y(vec.Y), Z(vec.Z), SVector3Reference<T>(X, Y, Z)
	{}
	
	template <typename U>
	SVector3(SVector3<U> const & vec)
		: X(vec.X), Y(vec.Y), Z(vec.Z), SVector3Reference<T>(X, Y, Z)
	{}

	SVector3(SVector3<T> const & vec)
		: X(vec.X), Y(vec.Y), Z(vec.Z), SVector3Reference<T>(X, Y, Z)
	{}
	
	template <typename U>
	SVector3(SVector2<U> xy, T z)
		: X(xy.X), Y(xy.Y), Z(z), SVector3Reference<T>(X, Y, Z)
	{}

	SVector3(glm::vec3 const & vec)
		: X(vec.x), Y(vec.y), Z(vec.z), SVector3Reference<T>(X, Y, Z)
	{}

	SVector3(T in)
		: X(in), Y(in), Z(in), SVector3Reference<T>(X, Y, Z)
	{}

	SVector3(T in_x, T in_y, T in_z)
		: X(in_x), Y(in_y), Z(in_z), SVector3Reference<T>(X, Y, Z)
	{}

	SVector3 & operator = (SVector3Reference<T> const & vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;

		return * this;
	}

	SVector3 & operator = (SVector3 const & vec)
	{
		X = vec.X;
		Y = vec.Y;
		Z = vec.Z;

		return * this;
	}

};

template <typename T>
SVector3<T> SVector3Reference<T>::crossProduct(SVector3Reference<T> const & v) const
{
    return SVector3<T>(Y*v.Z - v.Y*Z, v.X*Z - X*v.Z, X*v.Y - v.X*Y);
}

template <typename T>
SVector3<T> const SVector3Reference<T>::getNormalized() const
{
    SVector3<T> copy(* this);
    copy.normalize();
    return copy;
}

template <typename T>
SVector3<T> SVector3Reference<T>::operator + (SVector3<T> const & v) const
{
    return SVector3<T>(X+v.X, Y+v.Y, Z+v.Z);
}

template <typename T>
SVector3<T> SVector3Reference<T>::operator - (SVector3<T> const & v) const
{
    return SVector3<T>(X-v.X, Y-v.Y, Z-v.Z);
}

template <typename T>
SVector3<T> SVector3Reference<T>::operator * (SVector3<T> const & v) const
{
    return SVector3<T>(X*v.X, Y*v.Y, Z*v.Z);
}

template <typename T>
SVector3<T> SVector3Reference<T>::operator / (SVector3<T> const & v) const
{
    return SVector3<T>(X/v.X, Y/v.Y, Z/v.Z);
}

template <typename T>
SVector3<T> SVector3Reference<T>::operator * (T const s) const
{
    return SVector3<T>(X*s, Y*s, Z*s);
}

template <typename T>
SVector3<T> SVector3Reference<T>::operator / (T const s) const
{
    return SVector3<T>(X/s, Y/s, Z/s);
}

typedef SVector3<float> SVector3f;
typedef SVector3<double> SVector3d;

#endif
