#ifndef _CABBAGE_CORE_SPOSITION2_H_INCLUDED_
#define _CABBAGE_CORE_SPOSITION2_H_INCLUDED_

#include <cmath>

class SPosition2
{

public:

	int X, Y;

	int & Width, & Height;

	SPosition2()
		: X(0), Y(0), Width(X), Height(Y)
	{}

	SPosition2(int in)
		: X(in), Y(in), Width(X), Height(Y)
	{}

	SPosition2(int in_x, int in_y)
		: X(in_x), Y(in_y), Width(X), Height(Y)
	{}

	SPosition2(SPosition2 const & rhs)
		: X(rhs.X), Y(rhs.Y), Width(X), Height(Y)
	{}

	SPosition2 & operator = (SPosition2 const & oth)
	{
		X = oth.X;
		Y = oth.Y;

		return * this;
	}

	int const operator[] (int i) const
	{
		return (i == 0 ? X : Y);
	}

	int & operator[] (int i)
	{
		return (i == 0 ? X : Y);
	}

	bool const operator < (SPosition2 const & oth) const
	{
		return oth.X == X ? Y < oth.Y : X < oth.X;
	}

	void reset()
	{
		X = 0;
		Y = 0;
	}

	void set(int in)
	{
		X = in;
		Y = in;
	}

	void set(int in_x, int in_y)
	{
		X = in_x;
		Y = in_y;
	}

	int dotProduct(SPosition2 const & v) const
	{
		return X*v.X + Y*v.Y;
	}

	float length() const
	{
		return sqrtf(float(X*X) + float(Y*Y));
	}

	SPosition2 operator + (SPosition2 const & v) const
	{
		return SPosition2(X+v.X, Y+v.Y);
	}

	SPosition2 & operator += (SPosition2 const & v)
	{
		X += v.X;
		Y += v.Y;

		return * this;
	}

	SPosition2 operator - (SPosition2 const & v) const
	{
		return SPosition2(X-v.X, Y-v.Y);
	}

	SPosition2 & operator -= (SPosition2 const & v)
	{
		X -= v.X;
		Y -= v.Y;

		return * this;
	}

	SPosition2 operator * (SPosition2 const & v) const
	{
		return SPosition2(X*v.X, Y*v.Y);
	}

	SPosition2 & operator *= (SPosition2 const & v)
	{
		X *= v.X;
		Y *= v.Y;

		return * this;
	}

	SPosition2 operator / (SPosition2 const & v) const
	{
		return SPosition2(X/v.X, Y/v.Y);
	}

	SPosition2 & operator /= (SPosition2 const & v)
	{
		X /= v.X;
		Y /= v.Y;

		return * this;
	}

	SPosition2 operator * (int const s) const
	{
		return SPosition2(X*s, Y*s);
	}

	SPosition2 & operator *= (int const s)
	{
		X *= s;
		Y *= s;

		return * this;
	}

	SPosition2 operator / (int const s) const
	{
		return SPosition2(X/s, Y/s);
	}

	SPosition2 & operator /= (int const s)
	{
		X /= s;
		Y /= s;

		return * this;
	}

};

#include "SSize2.h"


#endif
