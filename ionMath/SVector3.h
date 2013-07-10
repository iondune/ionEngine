#ifndef _ION_CORE_SVECTOR3_H_INCLUDED_
#define _ION_CORE_SVECTOR3_H_INCLUDED_

#include <ionConfig.h>

#include "SVector.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


template <typename T>
class SVector3 : public SVector<T, 3, SVector3<T> >
{

public:

	T & X, & Y, & Z;

	//! Default constructor
	ION_FUNC_DEF SVector3()
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		SVectorBase<T, 3>::set((T) 0);
	}

	//! Scalar constructor
	ION_FUNC_DEF SVector3(T const in)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		SVectorBase<T, 3>::set(in);
	}

	//! Explicit constructor
	ION_FUNC_DEF SVector3(T const x, T const y, T const z)
		: X(Values[0]), Y(Values[1]), Z(Values[2])	
	{
		this->Values[0] = x;
		this->Values[1] = y;
		this->Values[2] = z;
	}

	//! Reference constructor
	ION_FUNC_DEF SVector3(T const & x, T const & y, T const & z, ForceReference)
		: X(x), Y(y), Z(z)
	{}

	//! Copy constructor
	ION_FUNC_DEF SVector3(SVector3<T> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		set(vec);
	}

	//! GLM constructor
	template <typename U>
	ION_FUNC_DEF SVector3(glm::detail::tvec3<U> const & v)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		Values[0] = (T) v.x;
		Values[1] = (T) v.y;
		Values[2] = (T) v.z;
	}
	
	//! Generic vector constructor
	template <typename U, int otherDimension, typename otherImplementation>
	ION_FUNC_DEF SVector3(SVector<U, otherDimension, otherImplementation> const & vec)
		: X(Values[0]), Y(Values[1]), Z(Values[2])
	{
		SVectorBase<T, 3>::set(vec);
	}

	//! Assignment operator
	ION_FUNC_DEF SVector3<T> & operator = (SVector3<T> const & vec)
	{
		set(vec);

		return * this;
	}
	
	//! Generic vector assignment operator
	template <typename U, int otherDimension>
	ION_FUNC_DEF SVector3<T> & operator = (SVectorBase<U, otherDimension> const & vec)
	{
		set(vec);

		return * this;
	}
	
	//! Vector cross product
	template <typename U, typename otherImplementation>
	ION_FUNC_DEF SVector3<T> crossProduct(SVector<U, 3, otherImplementation> const & v) const
	{
		return SVector3<T>(Y*v.Values[2] - v.Values[1]*Z, v.Values[0]*Z - X*v.Values[2], X*v.Values[1] - v.Values[0]*Y);
	}

	ION_FUNC_DEF glm::vec3 const getGLMVector() const
	{
		return glm::vec3(X, Y, Z);
	}

	ION_FUNC_DEF friend std::ostream & operator << (std::ostream & stream, SVector3<T> const & vec)
	{
		return stream << vec.X << " " << vec.Y << " " << vec.Z;
	}

	ION_FUNC_DEF SVector3<T> rotateAround(SVector3<T> const & other, f32 const radians) const
	{
		glm::mat4 matrix = glm::rotate(glm::mat4(1.f), radians, other.getGLMVector());
		glm::vec4 temp = glm::vec4(getGLMVector(), 1.f) * matrix;
		
		SVector3<T> out(temp.x, temp.y, temp.z);
		return out;
	}

};

typedef SVector3<f32> SVector3f;
typedef SVector3<f64> SVector3d;
typedef SVector3<s32> SVector3i;
typedef SVector3<u32> SVector3u;

typedef SVector3f vec3f;
typedef SVector3d vec3d;
typedef SVector3i vec3i;
typedef SVector3u vec3u;

#endif
