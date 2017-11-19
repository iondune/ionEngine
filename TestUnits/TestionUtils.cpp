
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("ionUtils::DigitCount", "")
{
	CHECK(DigitCount(0) == 1);
	CHECK(DigitCount(1) == 1);
	CHECK(DigitCount(5) == 1);
	CHECK(DigitCount(9) == 1);
	CHECK(DigitCount(10) == 2);
	CHECK(DigitCount(11) == 2);
	CHECK(DigitCount(19) == 2);
	CHECK(DigitCount(20) == 2);
	CHECK(DigitCount(99) == 2);
	CHECK(DigitCount(100) == 3);
	CHECK(DigitCount(101) == 3);
	CHECK(DigitCount(1000) == 4);
	CHECK(DigitCount(1001) == 4);
	CHECK(DigitCount(9999) == 4);
	CHECK(DigitCount(10000) == 5);
	CHECK(DigitCount(10001) == 5);
	CHECK(DigitCount(34802) == 5);
	CHECK(DigitCount(2147483647) == 10);

	CHECK(DigitCount(-0) == 1);
	CHECK(DigitCount(-1) == 2);
	CHECK(DigitCount(-9) == 2);
	CHECK(DigitCount(-10) == 3);
	CHECK(DigitCount(-11) == 3);
	CHECK(DigitCount(-99) == 3);
	CHECK(DigitCount(-100) == 4);
	CHECK(DigitCount(-234098) == 7);
	CHECK(DigitCount(-82093480) == 9);
}

TEST_CASE("ionUtils::Clamp", "")
{
	CHECK(Clamp<int>(0, -1, 1) == 0);
	CHECK(Clamp<int>(0, 0, 1) == 0);
	CHECK(Clamp<int>(1, 1, 3) == 1);
	CHECK(Clamp<int>(5, 1, 3) == 3);
}

TEST_CASE("ionUtils::Sq", "")
{
	CHECK(Sq<int>(0) == 0);
	CHECK(Sq<int>(1) == 1);
	CHECK(Sq<int>(2) == 4);
	CHECK(Sq<int>(3) == 9);
	CHECK(Sq<int>(-1) == 1);
}

TEST_CASE("ionUtils::Average2", "")
{
	CHECK(Average<int>(2, 4) == 3);
	CHECK(Average<int>(4, 2) == 3);
	CHECK(Average<int>(3, 4) == 3);
	CHECK(Average<int>(4, 4) == 4);
	CHECK(Average<int>(0, 13) == 6);
	CHECK(Average<int>(99, 101) == 100);
	CHECK(Average<int>(-2934, 2934) == 0);
	CHECK(Average<int>(0, 0) == 0);

	CHECK(Average<float>(2, 4) == 3);
	CHECK(Average<float>(3, 4) == 3.5);
}

TEST_CASE("ionUtils::Average3,4", "")
{
	CHECK(Average<int>(2, 4, 6) == 4);
	CHECK(Average<int>(6, 4, 2) == 4);
	CHECK(Average<int>(4, 4, 4) == 4);
	CHECK(Average<int>(3, 3, 4) == 3);
	CHECK(Average<int>(1, 3, 4) == 2);
	CHECK(Average<int>(7, 3, 4) == 4);
	CHECK(Average<int>(7, 3, 5) == 5);
	CHECK(Average<int>(-1, 3, 4) == 2);
	CHECK(Average<int>(0, -2934, 2934) == 0);

	CHECK(Average<int>(2, 4, 6, 4) == 4);
	CHECK(Average<int>(6, 4, 2, 0) == 3);
	CHECK(Average<int>(4, 4, 4, 4) == 4);
	CHECK(Average<int>(3, 3, 4, 3) == 3);
	CHECK(Average<int>(1, 3, 4, 2) == 2);
	CHECK(Average<int>(7, 3, 4, 1) == 3);
	CHECK(Average<int>(7, 3, 5, 1) == 4);
	CHECK(Average<int>(-1, 3, 4, -1) == 1);
	CHECK(Average<int>(0, -2934, 2934, 0) == 0);
}

TEST_CASE("ionUtils::Sign")
{
	CHECK(Sign<int>(0) == 0);
	CHECK(Sign<int>(1) == 1);
	CHECK(Sign<int>(-1) == -1);
	CHECK(Sign<int>(-5) == -1);
	CHECK(Sign<int>(2) == 1);
	CHECK(Sign<int>(2147483647) == 1);
	CHECK(Sign<int>(-2147483647) == -1);

	CHECK(Sign<uint>(0) == 0);
	CHECK(Sign<uint>(-1) == 1);
	CHECK(Sign<uint>(1) == 1);
	CHECK(Sign<uint>(4294967295) == 1);

	CHECK(Sign<float>(0.f) == 0);
	CHECK(Sign<float>(0.1f) == 1);
	CHECK(Sign<float>(-0.1f) == -1);
	CHECK(Sign<float>(RoundingError32) == 1);
	CHECK(Sign<float>(-RoundingError32) == -1);
	CHECK(Sign<float>(std::numeric_limits<float>::max()) == 1);
	CHECK(Sign<float>(-std::numeric_limits<float>::max()) == -1);
}

TEST_CASE("ionUtils::MakeEven")
{
	CHECK(MakeEven(0) == 0);
	CHECK(MakeEven(1) == 0);
	CHECK(MakeEven(2) == 2);
	CHECK(MakeEven(3) == 2);
	CHECK(MakeEven(4) == 4);

	CHECK(MakeEven(-1) == -2);
	CHECK(MakeEven(-2) == -2);
	CHECK(MakeEven(-3) == -4);
	CHECK(MakeEven(-4) == -4);
}
