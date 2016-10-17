
#pragma once

#include "SVector3.h"


template <typename T>
class STriangle2
{

public:

	vec2<T> Vertices[3];

	STriangle2()
	{}

	STriangle2(vec2<T> const & v1, vec2<T> const & v2, vec2<T> const & v3)
	{
		Vertices[0] = v1;
		Vertices[1] = v2;
		Vertices[2] = v3;
	}

	static T Sign(vec2<T> const & p1, vec2<T> const & p2, vec2<T> const & p3)
	{
		return (p1.X - p3.X) * (p2.Y - p3.Y) - (p2.X - p3.X) * (p1.Y - p3.Y);
	}

	bool PointInside(vec2<T> const & pt) const
	{
		bool b1, b2, b3;

		b1 = Sign(pt, Vertices[0], Vertices[1]) < 0.0f;
		b2 = Sign(pt, Vertices[1], Vertices[2]) < 0.0f;
		b3 = Sign(pt, Vertices[2], Vertices[0]) < 0.0f;

		return ((b1 == b2) && (b2 == b3));
	}

};

typedef STriangle2<f32> STriangle2f;
typedef STriangle2<f64> STriangle2d;
typedef STriangle2<s32> STriangle2i;
typedef STriangle2<u32> STriangle2u;

typedef STriangle2f tri2f;
typedef STriangle2d tri2d;
typedef STriangle2i tri2i;
typedef STriangle2u tri2u;
