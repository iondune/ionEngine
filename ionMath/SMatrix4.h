#ifndef _ION_CORE_SMATRIX4_H_INCLUDED_
#define _ION_CORE_SMATRIX4_H_INCLUDED_

#include <ionConfig.h>

#include "SVector3.h"
#include "SVector4.h"


template <typename T>
class SMatrix4
{

public:

	typedef SVector4<T> Column;
	Column Columns[4];

	ION_FUNC_DEF SMatrix4()
	{
		Columns[0] = Column(1, 0, 0, 0);
		Columns[1] = Column(0, 1, 0, 0);
		Columns[2] = Column(0, 0, 1, 0);
		Columns[3] = Column(0, 0, 0, 1);
	}

	ION_FUNC_DEF SMatrix4(T const Scalar)
	{
		Columns[0] = Column(Scalar, 0, 0, 0);
		Columns[1] = Column(0, Scalar, 0, 0);
		Columns[2] = Column(0, 0, Scalar, 0);
		Columns[3] = Column(0, 0, 0, Scalar);
	}

	ION_FUNC_DEF SMatrix4(
		T const x0, T const y0, T const z0, T const w0,
		T const x1, T const y1, T const z1, T const w1,
		T const x2, T const y2, T const z2, T const w2,
		T const x3, T const y3, T const z3, T const w3)
	{
		Columns[0] = Column(x0, y0, z0, w0);
		Columns[1] = Column(x1, y1, z1, w1);
		Columns[2] = Column(x2, y2, z2, w2);
		Columns[3] = Column(x3, y3, z3, w3);
	}
	
	ION_FUNC_DEF Column const & operator[] (u32 const index) const
	{
		return Columns[index];
	}

	ION_FUNC_DEF Column & operator[] (u32 const index)
	{
		return Columns[index];
	}
	
	ION_FUNC_DEF SMatrix4<T> translate(SVector3<T> const & v) const
	{
		SMatrix4<T> Result(*this);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
	}

	ION_FUNC_DEF SMatrix4<T> rotate(T const & angle, SVector3<T> const & v) const
	{
		SMatrix4 const & m = *this;

		T a = angle;
		T c = cos(a);
		T s = sin(a);

		SVector3<T> axis = normalize(v);
		SVector3<T> temp = (T(1) - c) * axis;

		SMatrix4<T> Rotate(0.f);
		Rotate[0][0] = c + temp[0] * axis[0];
		Rotate[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
		Rotate[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

		Rotate[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
		Rotate[1][1] = c + temp[1] * axis[1];
		Rotate[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

		Rotate[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
		Rotate[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
		Rotate[2][2] = c + temp[2] * axis[2];

		SMatrix4<T> Result(0.f);
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
	}

	ION_FUNC_DEF SMatrix4<T> scale(SVector3<T> const & v)
	{
		SMatrix4 const & m = *this;

		SMatrix4<T> Result(SMatrix4<T>::null);
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
	}

	ION_FUNC_DEF SVector4<T> operator* (SVector4<T> const & v) const
	{
		return SVector4<T>(
			Columns[0][0] * v.x + Columns[1][0] * v.y + Columns[2][0] * v.z + Columns[3][0] * v.w,
			Columns[0][1] * v.x + Columns[1][1] * v.y + Columns[2][1] * v.z + Columns[3][1] * v.w,
			Columns[0][2] * v.x + Columns[1][2] * v.y + Columns[2][2] * v.z + Columns[3][2] * v.w,
			Columns[0][3] * v.x + Columns[1][3] * v.y + Columns[2][3] * v.z + Columns[3][3] * v.w);
	}

};

#endif
