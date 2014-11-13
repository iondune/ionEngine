
#include <ionCore.h>
#include <catch.hpp>


TEST_CASE("ionUtils::DigitCount", "")
{
	REQUIRE(DigitCount(0) == 1);
	REQUIRE(DigitCount(1) == 1);
	REQUIRE(DigitCount(5) == 1);
	REQUIRE(DigitCount(9) == 1);
	REQUIRE(DigitCount(10) == 2);
	REQUIRE(DigitCount(11) == 2);
	REQUIRE(DigitCount(19) == 2);
	REQUIRE(DigitCount(20) == 2);
	REQUIRE(DigitCount(99) == 2);
	REQUIRE(DigitCount(100) == 3);
	REQUIRE(DigitCount(101) == 3);
	REQUIRE(DigitCount(1000) == 4);
	REQUIRE(DigitCount(1001) == 4);
	REQUIRE(DigitCount(9999) == 4);
	REQUIRE(DigitCount(10000) == 5);
	REQUIRE(DigitCount(10001) == 5);
	REQUIRE(DigitCount(34802) == 5);
	REQUIRE(DigitCount(2147483647) == 10);

	REQUIRE(DigitCount(-0) == 1);
	REQUIRE(DigitCount(-1) == 2);
	REQUIRE(DigitCount(-9) == 2);
	REQUIRE(DigitCount(-10) == 3);
	REQUIRE(DigitCount(-11) == 3);
	REQUIRE(DigitCount(-99) == 3);
	REQUIRE(DigitCount(-100) == 4);
	REQUIRE(DigitCount(-234098) == 7);
	REQUIRE(DigitCount(-82093480) == 9);
}

TEST_CASE("ionUtils::Clamp", "")
{
	REQUIRE(Clamp<int>(0, -1, 1) == 0);
	REQUIRE(Clamp<int>(0, 0, 1) == 0);
	REQUIRE(Clamp<int>(1, 1, 3) == 1);
	REQUIRE(Clamp<int>(5, 1, 3) == 3);
}

TEST_CASE("ionUtils::Sq", "")
{
	REQUIRE(Sq<int>(0) == 0);
	REQUIRE(Sq<int>(1) == 1);
	REQUIRE(Sq<int>(2) == 4);
	REQUIRE(Sq<int>(3) == 9);
	REQUIRE(Sq<int>(-1) == 1);
}

TEST_CASE("ionUtils::Average2", "")
{
	REQUIRE(Average<int>(2, 4) == 3);
	REQUIRE(Average<int>(4, 2) == 3);
	REQUIRE(Average<int>(3, 4) == 3);
	REQUIRE(Average<int>(4, 4) == 4);
	REQUIRE(Average<int>(0, 13) == 6);
	REQUIRE(Average<int>(99, 101) == 100);
	REQUIRE(Average<int>(-2934, 2934) == 0);
	REQUIRE(Average<int>(0, 0) == 0);

	REQUIRE(Average<float>(2, 4) == 3);
	REQUIRE(Average<float>(3, 4) == 3.5);
}
