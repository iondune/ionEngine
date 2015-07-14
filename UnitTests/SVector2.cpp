
#include <ionMath.h>
#include <catch.hpp>


TEST_CASE("SVector2::operator <", "Check that operator < works consistently")
{
	map<vec2i, int> Map;
	Map[vec2i(-1, -1)] = 3;
	Map[vec2i(0, -1)] = 4;

	auto it = Map.begin();
	REQUIRE(it->first.X == -1);
	REQUIRE(it->first.Y == -1);
	REQUIRE(it->second == 3);
	it ++;
	REQUIRE(it->first.X == 0);
	REQUIRE(it->first.Y == -1);
	REQUIRE(it->second == 4);

	REQUIRE(vec2i(-1, -1) < vec2i(0, -1));
	REQUIRE(! (vec2i(-1, -1) > vec2i(0, -1)));
	REQUIRE(! (vec2i(0, 0) < vec2i(0, 0)));
	REQUIRE(! (vec2i(2, 2) < vec2i(2, 2)));
	REQUIRE(! (vec2i(-2, 2) < vec2i(-2, 2)));
	REQUIRE(! (vec2i(2, -2) < vec2i(2, -2)));

	REQUIRE(vec2i(-4, -4) < vec2i(-3, -10));
	REQUIRE(vec2i(-4, -4) < vec2i(-3, 10));
	REQUIRE(vec2i(-4, -4) < vec2i(-4, -3));
}

TEST_CASE("SVector2::operator >", "Check that operator > works consistently")
{
	REQUIRE(vec2i(0, -1) > vec2i(-1, -1));
	REQUIRE(! (vec2i(0, 0) > vec2i(0, 0)));
	REQUIRE(! (vec2i(2, 2) > vec2i(2, 2)));
	REQUIRE(! (vec2i(-2, 2) > vec2i(-2, 2)));
	REQUIRE(! (vec2i(2, -2) > vec2i(2, -2)));

	REQUIRE(vec2i(-3, -10) > vec2i(-4, -4));
	REQUIRE(vec2i(-3, 10) > vec2i(-4, -4));
	REQUIRE(vec2i(-4, -3) > vec2i(-4, -4));
}
