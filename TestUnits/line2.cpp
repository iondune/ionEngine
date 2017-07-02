
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
