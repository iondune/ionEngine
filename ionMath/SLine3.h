
#pragma once

#include "SVector3.h"


//! \brief 3D line segment
//! \ingroup ionMath
template <typename T, typename Vector = vec3<T> >
class SLine3
{

	typedef SLine3<T, Vector> Type;

public:

	Vector Start, End;

	SLine3(Vector const & start, Vector const & end)
		: Start(start), End(end)
	{}

	Vector GetMiddle() const
	{
		return (Start + End) / 2;
	}

	Vector GetVector() const
	{
		return Start - End;
	}

	T Length() const
	{
		return GetVector().Length();
	}

	friend T Length(Type const & Line)
	{
		return Line.GetVector().Length();
	}

};

typedef SLine3<float> SLine3f;
typedef SLine3<double> SLine3d;
typedef SLine3<int> SLine3i;

typedef SLine3<float> line3f;
typedef SLine3<double> line3d;
typedef SLine3<int> line3i;
