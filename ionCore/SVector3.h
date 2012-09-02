#ifndef _CABBAGE_CORE_SVECTOR3_H_INCLUDED_
#define _CABBAGE_CORE_SVECTOR3_H_INCLUDED_

#include "SVector.h"

#include <glm/glm.hpp>


template <typename T>
class SVector3 : public SVector<T, 3, SVector3<T> >
{

public:

	T & X, & Y, & Z;

	SVector3()
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		SVectorSimple<T, Dimension>::set((T) 0);
	}

	SVector3(T const in)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		SVectorSimple<T, Dimension>::set(in);
	}

	SVector3(T const x, T const y, T const z)
		: X(Values[0]), Y(Values[1]), Z(Values[2])	
	{
		Values[0] = x;
		Values[1] = y;
		Values[2] = z;
	}

	SVector3(T const & x, T const & y, T const & z, ForceReference)
		: X(x), Y(y), Z(z)
	{}

	SVector3(SVector3<T> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		set(vec);
	}

	template <typename U>
	SVector3(glm::detail::tvec3<U> const & v)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		Values[0] = (T) v.x;
		Values[1] = (T) v.y;
		Values[2] = (T) v.z;
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SVector3(SVector<U, otherDimension, otherImplementation> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		set(vec);
	}

	SVector3<T> & operator = (SVector3<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	template <typename U, int otherDimension, typename otherImplementation>
	SVector3<T> & operator = (SVector<U, otherDimension, otherImplementation> const & vec)
	{
		set(v);

		return * this;
	}
	
	template <typename U, typename otherImplementation>
	SVector3<T> crossProduct(SVector<U, 3, otherImplementation> const & v) const
	{
		return SVector3<T>(Y*v.Values[2] - v.Values[1]*Z, v.Values[0]*Z - X*v.Values[2], X*v.Values[1] - v.Values[0]*Y);
	}

	glm::vec3 const getGLMVector() const
	{
		return glm::vec3(X, Y, Z);
	}

};

typedef SVector3<float> SVector3f;
typedef SVector3<double> SVector3d;
typedef SVector3<int> SVector3i;
typedef SVector3<unsigned int> SVector3u;

#endif
