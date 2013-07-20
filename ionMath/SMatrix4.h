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
		Column v1, Column v2, Column v3, Column v4)
	{
		Columns[0] = v1;
		Columns[1] = v2;
		Columns[2] = v3;
		Columns[3] = v4;
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

	ION_FUNC_DEF SMatrix4<T>(SMatrix4<T> const & other)
	{
		Columns[0] = other.Columns[0];
		Columns[1] = other.Columns[1];
		Columns[2] = other.Columns[2];
		Columns[3] = other.Columns[3];
	}

	ION_FUNC_DEF SMatrix4<T> & operator =(SMatrix4<T> const & other)
	{
		Columns[0] = other.Columns[0];
		Columns[1] = other.Columns[1];
		Columns[2] = other.Columns[2];
		Columns[3] = other.Columns[3];

		return *this;
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
		Result[3] = Columns[0] * v[0] + Columns[1] * v[1] + Columns[2] * v[2] + Columns[3];
		//printf("Position %f %f %f TM %f %f %f %f\n", v[0], v[1], v[2],
		//	Result[3][0], Result[3][1], Result[3][2], Result[3][3]);
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

		SMatrix4<T> Result(0.f);
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
	}

	ION_FUNC_DEF SMatrix4<T> & operator /=(SMatrix4<T> const & m)
	{
		return (*this = *this / m);
	}

	ION_FUNC_DEF SMatrix4<T> operator /(SMatrix4<T> const & m)
	{
		return SMatrix4(
			Columns[0] / m[0],
			Columns[1] / m[1],
			Columns[2] / m[2],
			Columns[3] / m[3]);
	}

	ION_FUNC_DEF SMatrix4<T> & operator /=(f32 const & s)
	{
		return (*this = *this / s);
	}

	ION_FUNC_DEF SMatrix4<T> operator /(f32 const & s)
	{
		return SMatrix4(
			Columns[0] / s,
			Columns[1] / s,
			Columns[2] / s,
			Columns[3] / s);
	}

	ION_FUNC_DEF SMatrix4<T> & operator *=(SMatrix4<T> const & m)
	{
		return (*this = *this * m);
	}

	ION_FUNC_DEF SMatrix4<T> operator *(SMatrix4<T> const & m2)
	{
		SMatrix4 const & m1 = *this;

		Column const SrcA0 = m1[0];
		Column const SrcA1 = m1[1];
		Column const SrcA2 = m1[2];
		Column const SrcA3 = m1[3];

		Column const SrcB0 = m2[0];
		Column const SrcB1 = m2[1];
		Column const SrcB2 = m2[2];
		Column const SrcB3 = m2[3];

		SMatrix4<T> Result(0);
		Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1] + SrcA2 * SrcB0[2] + SrcA3 * SrcB0[3];
		Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1] + SrcA2 * SrcB1[2] + SrcA3 * SrcB1[3];
		Result[2] = SrcA0 * SrcB2[0] + SrcA1 * SrcB2[1] + SrcA2 * SrcB2[2] + SrcA3 * SrcB2[3];
		Result[3] = SrcA0 * SrcB3[0] + SrcA1 * SrcB3[1] + SrcA2 * SrcB3[2] + SrcA3 * SrcB3[3];
		return Result;
	}

	ION_FUNC_DEF SVector4<T> operator *(SVector4<T> const & v) const
	{
		return SVector4<T>(
			Columns[0][0] * v.X + Columns[1][0] * v.Y + Columns[2][0] * v.Z + Columns[3][0] * v.W,
			Columns[0][1] * v.X + Columns[1][1] * v.Y + Columns[2][1] * v.Z + Columns[3][1] * v.W,
			Columns[0][2] * v.X + Columns[1][2] * v.Y + Columns[2][2] * v.Z + Columns[3][2] * v.W,
			Columns[0][3] * v.X + Columns[1][3] * v.Y + Columns[2][3] * v.Z + Columns[3][3] * v.W);
			
			/*Columns[0][0] * v.X + Columns[0][1] * v.Y + Columns[0][2] * v.Z + Columns[0][3] * v.W,
			Columns[1][0] * v.X + Columns[1][1] * v.Y + Columns[1][2] * v.Z + Columns[1][3] * v.W,
			Columns[2][0] * v.X + Columns[2][1] * v.Y + Columns[2][2] * v.Z + Columns[2][3] * v.W,
			Columns[3][0] * v.X + Columns[3][1] * v.Y + Columns[3][2] * v.Z + Columns[3][3] * v.W);*/
	}

	ION_FUNC_DEF SMatrix4<T> inverse() const
	{
		T Coef00 = Columns[2][2] * Columns[3][3] - Columns[3][2] * Columns[2][3];
		T Coef02 = Columns[1][2] * Columns[3][3] - Columns[3][2] * Columns[1][3];
		T Coef03 = Columns[1][2] * Columns[2][3] - Columns[2][2] * Columns[1][3];

		T Coef04 = Columns[2][1] * Columns[3][3] - Columns[3][1] * Columns[2][3];
		T Coef06 = Columns[1][1] * Columns[3][3] - Columns[3][1] * Columns[1][3];
		T Coef07 = Columns[1][1] * Columns[2][3] - Columns[2][1] * Columns[1][3];

		T Coef08 = Columns[2][1] * Columns[3][2] - Columns[3][1] * Columns[2][2];
		T Coef10 = Columns[1][1] * Columns[3][2] - Columns[3][1] * Columns[1][2];
		T Coef11 = Columns[1][1] * Columns[2][2] - Columns[2][1] * Columns[1][2];

		T Coef12 = Columns[2][0] * Columns[3][3] - Columns[3][0] * Columns[2][3];
		T Coef14 = Columns[1][0] * Columns[3][3] - Columns[3][0] * Columns[1][3];
		T Coef15 = Columns[1][0] * Columns[2][3] - Columns[2][0] * Columns[1][3];

		T Coef16 = Columns[2][0] * Columns[3][2] - Columns[3][0] * Columns[2][2];
		T Coef18 = Columns[1][0] * Columns[3][2] - Columns[3][0] * Columns[1][2];
		T Coef19 = Columns[1][0] * Columns[2][2] - Columns[2][0] * Columns[1][2];

		T Coef20 = Columns[2][0] * Columns[3][1] - Columns[3][0] * Columns[2][1];
		T Coef22 = Columns[1][0] * Columns[3][1] - Columns[3][0] * Columns[1][1];
		T Coef23 = Columns[1][0] * Columns[2][1] - Columns[2][0] * Columns[1][1];

		SVector4<T> const SignA(+1, -1, +1, -1);
		SVector4<T> const SignB(-1, +1, -1, +1);

		SVector4<T> Fac0(Coef00, Coef00, Coef02, Coef03);
		SVector4<T> Fac1(Coef04, Coef04, Coef06, Coef07);
		SVector4<T> Fac2(Coef08, Coef08, Coef10, Coef11);
		SVector4<T> Fac3(Coef12, Coef12, Coef14, Coef15);
		SVector4<T> Fac4(Coef16, Coef16, Coef18, Coef19);
		SVector4<T> Fac5(Coef20, Coef20, Coef22, Coef23);

		SVector4<T> Vec0(Columns[1][0], Columns[0][0], Columns[0][0], Columns[0][0]);
		SVector4<T> Vec1(Columns[1][1], Columns[0][1], Columns[0][1], Columns[0][1]);
		SVector4<T> Vec2(Columns[1][2], Columns[0][2], Columns[0][2], Columns[0][2]);
		SVector4<T> Vec3(Columns[1][3], Columns[0][3], Columns[0][3], Columns[0][3]);

		SVector4<T> Inv0 = SignA * (Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		SVector4<T> Inv1 = SignB * (Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		SVector4<T> Inv2 = SignA * (Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		SVector4<T> Inv3 = SignB * (Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		SMatrix4<T> Inverse(Inv0, Inv1, Inv2, Inv3);

		SVector4<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		T Determinant = Columns[0].dotProduct(Row0);

		Inverse /= Determinant;

		return Inverse;
	}

};


typedef SMatrix4<f32> SMatrix4f;
typedef SMatrix4<f64> SMatrix4d;

typedef SMatrix4f mat4f;
typedef SMatrix4d mat4d;

#endif
