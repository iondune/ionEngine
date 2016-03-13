
#include <ionMath.h>
#include <catch.hpp>


TEST_CASE("SVector2::operator <")
{
	CHECK(vec2i(-1, -1) < vec2i(0, -1));
	CHECK(! (vec2i(0, 0) < vec2i(0, 0)));
	CHECK(! (vec2i(2, 2) < vec2i(2, 2)));
	CHECK(! (vec2i(-2, 2) < vec2i(-2, 2)));
	CHECK(! (vec2i(2, -2) < vec2i(2, -2)));

	CHECK(vec2i(-4, -4) < vec2i(-3, -10));
	CHECK(vec2i(-4, -4) < vec2i(-3, 10));
	CHECK(vec2i(-4, -4) < vec2i(-4, -3));
}

TEST_CASE("SVector2 used as a map index (uses operator <)")
{
	map<vec2i, int> Map;
	Map[vec2i(-1, -1)] = 3;
	Map[vec2i(0, -1)] = 4;

	REQUIRE(Map.size() == 2);

	auto it = Map.begin();
	CHECK(it->first.X == -1);
	CHECK(it->first.Y == -1);
	CHECK(it->second == 3);
	it ++;
	CHECK(it->first.X == 0);
	CHECK(it->first.Y == -1);
	CHECK(it->second == 4);
}
