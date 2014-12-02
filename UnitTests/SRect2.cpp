
#include <ionMath.h>
#include <catch.hpp>


TEST_CASE("SRect2::SRect")
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

TEST_CASE("SRect2::OtherCorner")
{
	REQUIRE(rect2i(3, 4, 10, 11).OtherCorner() == vec2i(13, 15));
	REQUIRE(rect2i(-1, -7, -13, 42).OtherCorner() == vec2i(-14, 35));
}

TEST_CASE("SRect2::GetCenter")
{
	REQUIRE(rect2i(0, 0, 4, 4).GetCenter() == vec2i(2, 2));
	REQUIRE(rect2i(0, 0, 3, 3).GetCenter() == vec2i(1, 1));
	REQUIRE(rect2i(0, 0, 2, 2).GetCenter() == vec2i(1, 1));
	REQUIRE(rect2i(0, 0, 1, 1).GetCenter() == vec2i(0, 0));
	REQUIRE(rect2i(0, 0, 0, 0).GetCenter() == vec2i(0, 0));
	REQUIRE(rect2i(3, 4, 10, 11).GetCenter() == vec2i(8, 9));
	REQUIRE(rect2i(1000000, 1000000, 10, 10).GetCenter() == vec2i(1000005));
	REQUIRE(rect2i(1000000000, 1000000000, 10, 10).GetCenter() == vec2i(1000000005));
	REQUIRE(rect2i(0, 0, 1000000000, 1000000000).GetCenter() == vec2i(500000000));
	REQUIRE(rect2i(0, 0, 2147483647, 2147483647).GetCenter() == vec2i(1073741823));

	REQUIRE(rect2f(0, 0, 4, 4).GetCenter() == vec2f(2, 2));
	REQUIRE(rect2f(0, 0, 5, 5).GetCenter() == vec2f(2.5f, 2.5f));
	REQUIRE(rect2d(0, 0, 2147483647, 2147483647).GetCenter() == vec2d(2147483647 / 2.0));
	REQUIRE(rect2d(vec2d(0), vec2d(1000000000000.0)).GetCenter() == vec2d(1000000000000.0 / 2.0));
	REQUIRE(rect2d(vec2d(0), vec2d(1000000000000000.0)).GetCenter() == vec2d(1000000000000000.0 / 2.0));
	REQUIRE(rect2d(vec2d(0), vec2d(100000000000000000000.0)).GetCenter() == vec2d(100000000000000000000.0 / 2.0));
}

TEST_CASE("SRect2::Intersects")
{
	REQUIRE(rect2i(0, 0, 1, 1).Intersects(rect2i(1, 1, 1, 1)));
	REQUIRE(rect2i(0, 0, 1, 1).Intersects(rect2i(1, 1, 0, 0)));
	REQUIRE(rect2i(1, 1, 0, 0).Intersects(rect2i(1, 1, 0, 0)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(11, 11, 0, 0)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(11, 11, 10, 10)));

	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(7, 4, 2, 5)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(5, 4, 2, 3)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(4, 7, 2, 5)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(4, 5, 2, 3)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(-3, 4, 4, 2)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(4, -3, 2, 4)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(5, 5, 0, 0)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(10, 10, 0, 0)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(5, 10, 0, 0)));
	REQUIRE(rect2i(0, 0, 10, 10).Intersects(rect2i(10, 10, 10, 10)));

	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(1, 11, 10, 10)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(1, -11, 10, 10)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(-11, 11, 10, 10)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(-11, 1, 10, 10)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(-11, -11, 10, 10)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(11, -11, 10, 10)));
	REQUIRE(! rect2i(0, 0, 10, 10).Intersects(rect2i(11, 1, 10, 10)));
}

