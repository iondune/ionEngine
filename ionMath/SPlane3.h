
#pragma once

#include "SVector3.h"


template <typename T, typename Vector = SVector3<T> >
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

	SPlane3(const Vector& point1, const Vector& point2, const Vector& point3)
	{
		SetPlane(point1, point2, point3);
	}

	SPlane3(const Vector & normal, const T d)
		: Normal(normal), D(d)
	{}

	void SetPlane(const Vector& point, const Vector& nvector)
	{
		Normal = nvector;
		RecalculateD(point);
	}

	void SetPlane(const Vector& nvect, T d)
	{
		Normal = nvect;
		D = d;
	}

	void SetPlane(const Vector& point1, const Vector& point2, const Vector& point3)
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
	bool GetIntersectionWithLine(const Vector& linePoint,
		const Vector& lineVect,
		Vector& outIntersection) const
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
	f32 GetKnownIntersectionWithLine(const Vector& linePoint1,
		const Vector& linePoint2) const
	{
		Vector vect = linePoint2 - linePoint1;
		T t2 = (f32)Normal.DotProduct(vect);
		return (f32)-((Normal.DotProduct(linePoint1) + D) / t2);
	}

	//! Get an intersection with a 3d line, limited between two 3d points.
	/** \param linePoint1 Point 1 of the line.
	\param linePoint2 Point 2 of the line.
	\param outIntersection Place to store the intersection point, if there is one.
	\return True if there was an intersection, false if there was not.
	*/
	bool GetIntersectionWithLimitedLine(
		const Vector& linePoint1,
		const Vector& linePoint2,
		Vector& outIntersection) const
	{
		return (GetIntersectionWithLine(linePoint1, linePoint2 - linePoint1, outIntersection) &&
			outIntersection.IsBetweenPoints(linePoint1, linePoint2));
	}

	//! Classifies the relation of a point to this plane.
	/** \param point Point to classify its relation.
	\return ISREL3D_FRONT if the point is in front of the plane,
	ISREL3D_BACK if the point is behind of the plane, and
	ISREL3D_PLANAR if the point is within the plane. */
	EIntersectionRelation ClassifyPointRelation(const Vector& point) const
	{
		const T d = Normal.DotProduct(point) + D;

		if (d < -RoundingError<T>)
			return EIntersectionRelation::Back;

		if (d > RoundingError<T>)
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
		return cross.getLength() > core::ROUNDING_ERROR_f32;
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
		const f64 det = fn00*fn11 - fn01*fn01;

		if (fabs(det) < ROUNDING_ERROR_f64 )
			return false;

		const f64 invdet = 1.0 / det;
		const f64 fc0 = (fn11*-D + fn01*other.D) * invdet;
		const f64 fc1 = (fn00*-other.D + fn01*D) * invdet;

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
		const f32 d = Normal.DotProduct(lookDirection);
		return F32_LOWER_EQUAL_0 ( d );
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

typedef SPlane3<f32> plane3f;
typedef SPlane3<s32> plane3i;
