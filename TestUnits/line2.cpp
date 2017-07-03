
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

	line2f e(vec2f(92.31f, 19.6f), vec2f(92.3f, 20.59f));
	line2f f(vec2f(92.48f, 19.68f), vec2f(19.76f, 21.51f));

	CHECK(e.IntersectsWith(f, Out));
	CHECK(f.IntersectsWith(e, Out));
}

TEST_CASE("line2 distance from line2")
{
	line2f a(vec2f(0, -1), vec2f(0, 1));
	line2f b(vec2f(-1, 0), vec2f(1, 0));

	CHECK(a.GetDistanceFrom(b) == Approx(0));

	line2f c(vec2f(0, 0), vec2f(0, 2));
	line2f d(vec2f(1, 1), vec2f(2, 1));

	CHECK(c.GetDistanceFrom(d) == Approx(1));

	line2f e(vec2f(0, 0), vec2f(1, 0));
	line2f f(vec2f(2, 1), vec2f(2, 2));

	CHECK(e.GetDistanceFrom(f) == Approx(Sqrt(2.f)));
}
