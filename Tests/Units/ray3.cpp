
#include <doctest.h>
#include <ionMath.h>

using namespace ion;


TEST_CASE("ray-sphere intersection")
{
	double Intersection;
	CHECK(ray3d(vec3d(0, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 9.0));

	CHECK(ray3d(vec3d(0.5, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1));
	CHECK(ray3d(vec3d(0.9, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1));
	CHECK(! ray3d(vec3d(1.1, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1));
	CHECK(! ray3d(vec3d(1.5, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1));
	CHECK(! ray3d(vec3d(2, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1));

	CHECK(ray3d(vec3d(2.5, 2, -8), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2), 1));
	CHECK(ray3d(vec3d(2.9, 2, -8), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2), 1));
	CHECK(! ray3d(vec3d(3.1, 2, -8), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2), 1));
	CHECK(! ray3d(vec3d(3.5, 2, -8), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2), 1));
	CHECK(! ray3d(vec3d(4, 2, -8), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2), 1));

	CHECK(ray3d(vec3d(2, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2, 0, 0), 1));
	CHECK(ray3d(vec3d(2, 5, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(2, 5, 0), 1));

	CHECK(ray3d(vec3d(0, 0, -2), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 1.0));
	CHECK(ray3d(vec3d(0, 0, -1.5), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 0.5));
	CHECK(ray3d(vec3d(0, 0, -1.01), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 0.01));

	CHECK(ray3d(vec3d(0, -10, 0), vec3d(0, 1, 0)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 9.0));
	CHECK(! ray3d(vec3d(0, 10, 0), vec3d(0, 1, 0)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(ray3d(vec3d(0, 10, 0), vec3d(0, -1, 0)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 9.0));

	CHECK(ray3d(vec3d(sqrt(2) / 2, 0, -10), vec3d(0, 0, 1)).IntersectsSphere(vec3d(0), 1, &Intersection));
	CHECK(Equals(Intersection, 10 - sqrt(2) / 2));
	vec3d Point = vec3d(0.5, 0, -10) + vec3d(0, 0, 1) * Intersection;
	CHECK(Equals(Point.X, 0.5));
	CHECK(Equals(Point.Y, 0.0));
	CHECK(Equals(Point.Z, -sqrt(2) / 2));
}

TEST_CASE("ray-box intersection")
{
	double Intersection;
	CHECK(ray3d(vec3d(0, 0, -10), vec3d(0, 0, 1)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(Equals(Intersection, 9.0));
	CHECK(! ray3d(vec3d(2, 0, -10), vec3d(0, 0, 1)).IntersectsBox(box3d(vec3d(-1), vec3d(1))));

	CHECK(ray3d(vec3d(0, 0, -2), vec3d(0, 0, 1)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(Equals(Intersection, 1.0));
	CHECK(ray3d(vec3d(0, 0, 0), vec3d(0, 0, 1)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(Equals(Intersection, 1.0));
	CHECK(ray3d(vec3d(0, 0, -1.5), vec3d(0, 0, 1)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(Equals(Intersection, 0.5));

	CHECK(ray3d(vec3d(0, -10, 0), vec3d(0, 1, 0)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(Equals(Intersection, 9.0));
	CHECK(! ray3d(vec3d(0, 10, 0), vec3d(0, 1, 0)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(ray3d(vec3d(0, 10, 0), vec3d(0, -1, 0)).IntersectsBox(box3d(vec3d(-1), vec3d(1)), &Intersection));
	CHECK(Equals(Intersection, 9.0));
}
