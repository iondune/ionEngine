
/* irrlicht.h -- interface of the 'Irrlicht Engine'

Copyright Original Work (C) 2002-2012 Nikolaus Gebhardt
Copyright Modified Work (C) 2017 Ian Dunn

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Please note that the Irrlicht Engine is based in part on the work of the
Independent JPEG Group, the zlib and the libPng. This means that if you use
the Irrlicht Engine in your product, you must acknowledge somewhere in your
documentation that you've used the IJG code. It would also be nice to mention
that you use the Irrlicht Engine, the zlib and libPng. See the README files
in the jpeglib, the zlib and libPng for further informations.
*/

#pragma once

#include "SVector3.h"


//! \brief 3D plane
//! \ingroup ionMath
template <typename T, typename Vector = vec3<T> >
class SPlane3
{

public:

	enum EIntersectionRelation
	{
		Front,
		Back,
		Plannar
	};

	SPlane3()
		: Normal(0, 1, 0)
	{
		RecalculateD(Vector(0,0,0));
	}

	SPlane3(const Vector& MPoint, const Vector& Normal)
		: Normal(Normal)
	{
		RecalculateD(MPoint);
	}

	SPlane3(T px, T py, T pz, T nx, T ny, T nz)
		: Normal(nx, ny, nz)
	{
		RecalculateD(Vector(px, py, pz));
	}

	SPlane3(Vector const & point1, Vector const & point2, Vector const & point3)
	{
		SetPlane(point1, point2, point3);
	}

	SPlane3(Vector const & normal, const T d)
		: Normal(normal), D(d)
	{}

	void SetPlane(Vector const & point, Vector const & nvector)
	{
		Normal = nvector;
		RecalculateD(point);
	}

	void SetPlane(Vector const & nvect, T d)
	{
		Normal = nvect;
		D = d;
	}

	void SetPlane(Vector const & point1, Vector const & point2, Vector const & point3)
	{
		// creates the plane from 3 memberpoints
		Normal = (point2 - point1).crossProduct(point3 - point1);
		Normal.normalize();

		RecalculateD(point1);
	}


	//! Get an intersection with a 3d line.
	/** \param lineVect Vector of the line to intersect with.
	\param linePoint Point of the line to intersect with.
	\param outIntersection Place to store the intersection point, if there is one.
	\return True if there was an intersection, false if there was not.
	*/
	bool GetIntersectionWithLine(Vector const & linePoint, Vector const & lineVect, Vector & outIntersection) const
	{
		T t2 = Normal.DotProduct(lineVect);

		if (t2 == 0)
			return false;

		T t =- (Normal.DotProduct(linePoint) + D) / t2;
		outIntersection = linePoint + (lineVect * t);
		return true;
	}

	//! Get percentage of line between two points where an intersection with this plane happens.
	/** Only useful if known that there is an intersection.
	\param linePoint1 Point1 of the line to intersect with.
	\param linePoint2 Point2 of the line to intersect with.
	\return Where on a line between two points an intersection with this plane happened.
	For example, 0.5 is returned if the intersection happened exactly in the middle of the two points.
	*/
	T GetKnownIntersectionWithLine(Vector const & linePoint1, Vector const & linePoint2) const
	{
		Vector vect = linePoint2 - linePoint1;
		T t2 = (T) Normal.DotProduct(vect);
		return (T) -((Normal.DotProduct(linePoint1) + D) / t2);
	}

	//! Get an intersection with a 3d line, limited between two 3d points.
	/** \param linePoint1 Point 1 of the line.
	\param linePoint2 Point 2 of the line.
	\param outIntersection Place to store the intersection point, if there is one.
	\return True if there was an intersection, false if there was not.
	*/
	bool GetIntersectionWithLimitedLine(Vector const & linePoint1, Vector const & linePoint2, Vector & outIntersection) const
	{
		return (GetIntersectionWithLine(linePoint1, linePoint2 - linePoint1, outIntersection) &&
			outIntersection.IsBetweenPoints(linePoint1, linePoint2));
	}

	//! Classifies the relation of a point to this plane.
	/** \param point Point to classify its relation.
	\return ISREL3D_FRONT if the point is in front of the plane,
	ISREL3D_BACK if the point is behind of the plane, and
	ISREL3D_PLANAR if the point is within the plane. */
	EIntersectionRelation ClassifyPointRelation(Vector const & point) const
	{
		const T d = Normal.DotProduct(point) + D;

		if (d < -RoundingError<T>::Value())
			return EIntersectionRelation::Back;

		if (d > RoundingError<T>::Value())
			return EIntersectionRelation::Front;

		return EIntersectionRelation::Plannar;
	}

	//! Recalculates the distance from origin by applying a new member point to the plane.
	void RecalculateD(const Vector& MPoint)
	{
		D = - MPoint.DotProduct(Normal);
	}

	//! Gets a member point of the plane.
	Vector GetMemberPoint() const
	{
		return Normal * -D;
	}

	//! Tests if there is an intersection with the other plane
	/** \return True if there is a intersection. */
	bool ExistsIntersection(const SPlane3<T>& other) const
	{
		Vector cross = other.Normal.CrossProduct(Normal);
		return cross.getLength() > RoundingError<T>::Value();
	}

	//! Intersects this plane with another.
	/** \param other Other plane to intersect with.
	\param outLinePoint Base point of intersection line.
	\param outLineVect Vector of intersection.
	\return True if there is a intersection, false if not. */
	bool GetIntersectionWithPlane(const SPlane3<T>& other,
		Vector& outLinePoint,
		Vector& outLineVect) const
	{
		const T fn00 = Normal.getLength();
		const T fn01 = Normal.DotProduct(other.Normal);
		const T fn11 = other.Normal.getLength();
		const T det = fn00*fn11 - fn01*fn01;

		if (fabs(det) < RoundingError<T>::Value())
			return false;

		const T invdet = 1 / det;
		const T fc0 = (fn11*-D + fn01*other.D) * invdet;
		const T fc1 = (fn00*-other.D + fn01*D) * invdet;

		outLineVect = Normal.CrossProduct(other.Normal);
		outLinePoint = Normal*(T)fc0 + other.Normal*(T)fc1;
		return true;
	}

	//! Get the intersection point with two other planes if there is one.
	bool GetIntersectionWithPlanes(const SPlane3<T>& o1,
		const SPlane3<T>& o2, Vector& outPoint) const
	{
		Vector linePoint, lineVect;
		if (GetIntersectionWithPlane(o1, linePoint, lineVect))
			return o2.GetIntersectionWithLine(linePoint, lineVect, outPoint);

		return false;
	}

	//! Test if the triangle would be front or backfacing from any point.
	/** Thus, this method assumes a camera position from
	which the triangle is definitely visible when looking into
	the given direction.
	Note that this only works if the normal is Normalized.
	Do not use this method with points as it will give wrong results!
	\param lookDirection: Look direction.
	\return True if the plane is front facing and
	false if it is backfacing. */
	bool IsFrontFacing(const Vector& lookDirection) const
	{
		const T d = Normal.DotProduct(lookDirection);
		return d <= 0 || Equals((T) 0, d);
	}

	//! Get the distance to a point.
	/** Note that this only works if the normal is normalized. */
	T GetDistanceTo(const Vector& point) const
	{
		return point.DotProduct(Normal) + D;
	}

	//! Normal vector of the plane.
	Vector Normal;

	//! Distance from origin.
	T D;
};

typedef SPlane3<float> plane3f;
typedef SPlane3<int> plane3i;
