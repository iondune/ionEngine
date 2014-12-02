
#include <ionMath.h>
#include <catch.hpp>


TEST_CASE("SRect2::SRect)")
{
	rect2i r1;
	REQUIRE(r1.Position == vec2i(0, 0));
	REQUIRE(r1.Size == vec2i(0, 0));

	rect2i r2(vec2i(3, 4), vec2i(10, 11));
	REQUIRE(r2.Position == vec2i(3, 4));
	REQUIRE(r2.Size == vec2i(10, 11));

	rect2i r3(3, 4, 10, 11);
	REQUIRE(r3.Position == vec2i(3, 4));
	REQUIRE(r3.Size == vec2i(10, 11));
}

