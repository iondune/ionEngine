
#include <ionMath.h>
#include <catch.hpp>


TEST_CASE("SBoundingBox3 basic operations")
{
	SBoundingBox3i bbi;

	bbi.MinCorner = vec3i(0, 0, 0);
	bbi.MaxCorner = vec3i(4, 6, 8);
	CHECK(bbi.GetCenter() == vec3i(2, 3, 4));
	CHECK(bbi.GetExtent() == vec3i(4, 6, 8));
}

TEST_CASE("SBoundingBox3i intersection")
{
	SBoundingBox3i a, b;

	a.MinCorner = vec3i(0, 0, 0);
	a.MaxCorner = vec3i(1, 1, 1);
	b.MinCorner = vec3i(1, 1, 1);
	b.MaxCorner = vec3i(2, 2, 2);
	CHECK(a.Intersects(b));

	a.MinCorner = vec3i(0, 0, 0);
	b.MaxCorner = vec3i(4, 6, 8);
	CHECK(a.Intersects(b));
	CHECK(b.GetExtent() == vec3i(3, 5, 7));
}

TEST_CASE("SBoundingBox3 ray intersection")
{
	SBoundingBox3f aabb;
	vec3f out;

	aabb.MinCorner = vec3f(0, 0, 0);
	aabb.MaxCorner = vec3f(4, 6, 8);
	CHECK(! aabb.IntersectsWithRay(vec3f(-1, 10, 1), vec3f(0, -1, 0), out));
	CHECK(! aabb.IntersectsWithRay(vec3f(1, 10, 1), vec3f(0, 1, 0), out));

	CHECK(aabb.IntersectsWithRay(vec3f(1, 10, 1), vec3f(0, -1, 0), out));
	CHECK(out == vec3f(1, 6, 1));

	CHECK(aabb.IntersectsWithRay(vec3f(2, 10, 2), vec3f(0, -1, 0), out));
	CHECK(out == vec3f(2, 6, 2));

	CHECK(! aabb.IntersectsWithRay(vec3f(2, 2, -2), vec3f(0, 0, -1), out));
	CHECK(aabb.IntersectsWithRay(vec3f(2, 2, -2), vec3f(0, 0, 1), out));
	CHECK(out == vec3f(2, 2, 0));

	CHECK(! aabb.IntersectsWithRay(vec3f(2, 2, 10), vec3f(0, 0, 1), out));
	CHECK(aabb.IntersectsWithRay(vec3f(2, 2, 10), vec3f(0, 0, -1), out));
	CHECK(out == vec3f(2, 2, 8));

	CHECK(aabb.IntersectsWithRay(vec3f(2, 2, 10), vec3f(0, 0, -2.1f), out));
	CHECK(out == vec3f(2, 2, 8));

	CHECK(aabb.IntersectsWithRay(vec3f(2, 2, 10), vec3f(0, 0, -3), out));
	CHECK(out == vec3f(2, 2, 8));
}
