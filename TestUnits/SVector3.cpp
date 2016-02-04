
#include <ionMath.h>
#include <catch.hpp>


TEST_CASE("SVector3::operator <", "Check that operator < works consistently")
{
	REQUIRE(vec3i(-1, -1, 0) < vec3i(0, -1, 0));
	REQUIRE(! (vec3i(-1, -1, 0) > vec3i(0, -1, 0)));
	REQUIRE(! (vec3i(0, 0, 0) < vec3i(0, 0, 0)));
	REQUIRE(! (vec3i(2, 2, 0) < vec3i(2, 2, 0)));
	REQUIRE(! (vec3i(-2, 2, 0) < vec3i(-2, 2, 0)));
	REQUIRE(! (vec3i(2, -2, 0) < vec3i(2, -2, 0)));

	REQUIRE(vec3i(-4, -4, 0) < vec3i(-3, -10, 0));
	REQUIRE(vec3i(-4, -4, 0) < vec3i(-3, 10, 0));
	REQUIRE(vec3i(-4, -4, 0) < vec3i(-4, -3, 0));

	REQUIRE(vec3i(0, 0, 0) < vec3i(0, 0, 1));
	REQUIRE(vec3i(0, 0, 0) < vec3i(0, 1, 0));
	REQUIRE(vec3i(0, 0, 0) < vec3i(1, 0, 0));
	REQUIRE(vec3i(0, 0, -1) < vec3i(0, 0, 0));
	REQUIRE(! (vec3i(0, 0, 1) < vec3i(0, 0, 0)));
	REQUIRE(! (vec3i(0, 1, 0) < vec3i(0, 0, 0)));
	REQUIRE(! (vec3i(1, 0, 0) < vec3i(0, 0, 0)));
	REQUIRE(! (vec3i(0, 0, 0) < vec3i(0, 0, -1)));
}
