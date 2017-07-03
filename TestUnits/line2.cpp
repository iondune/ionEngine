
#include <catch.hpp>
#include <ionMath.h>

using namespace ion;


TEST_CASE("line2 closest point", "")
{
	line2f l(vec2f(0, 0), vec2f(0, 1));

	CHECK(l.ClosestPointTo(vec2f(0, 0)) == vec2f(0, 0));
	CHECK(l.ClosestPointTo(vec2f(0, 1)) == vec2f(0, 1));
	CHECK(l.ClosestPointTo(vec2f(0, 2)) == vec2f(0, 1));
	CHECK(l.ClosestPointTo(vec2f(0, 3)) == vec2f(0, 1));
	CHECK(l.ClosestPointTo(vec2f(1, 1)) == vec2f(0, 1));
	CHECK(l.ClosestPointTo(vec2f(1, 0.5f)) == vec2f(0, 0.5f));
	CHECK(l.ClosestPointTo(vec2f(0, 0.5f)) == vec2f(0, 0.5f));
	CHECK(l.ClosestPointTo(vec2f(-1, 0.5f)) == vec2f(0, 0.5f));
}

TEST_CASE("line2 intersect")
{
	line2f a(vec2f(0, -1), vec2f(0, 1));
	line2f b(vec2f(-1, 0), vec2f(1, 0));
	vec2f Out = -1;

	CHECK(a.IntersectsWith(b, Out));
	CHECK(Out == vec2f(0, 0));
	CHECK(b.IntersectsWith(a, Out));
	CHECK(Out == vec2f(0, 0));

	line2f c(vec2f(0, 0), vec2f(0, 2));
	line2f d(vec2f(1, 1), vec2f(2, 1));

	CHECK(! c.IntersectsWith(d, Out));
	CHECK(! d.IntersectsWith(c, Out));
}
