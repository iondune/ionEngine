
#include <ionCore.h>
#include <catch.hpp>


TEST_CASE("ionComparison::RoundingError", "rounding error constants")
{
	REQUIRE(RoundingError<int>::Value() == 0);
	REQUIRE(RoundingError<uint>::Value() == 0);
	REQUIRE(RoundingError<float>::Value() == RoundingError32);
	REQUIRE(RoundingError<double>::Value() == RoundingError64);
}

TEST_CASE("ionComparison::Equals<T>", "equality function")
{
	REQUIRE(Equals(0, 0));
	REQUIRE(Equals(1, 1));
	REQUIRE(Equals(-1, -1));

	REQUIRE(! Equals(0, 1));
	REQUIRE(! Equals(-1, 1));

	REQUIRE(Equals(0u, 0u));
	REQUIRE(Equals(0.f, RoundingError32));
	REQUIRE(! Equals(0.f, 1.5f * RoundingError32));
	REQUIRE(Equals(0.0, RoundingError64));
	REQUIRE(! Equals(0.0, 1.5 * RoundingError64));
}

TEST_CASE("ionComparsion::Minimum2", "minimum of two operands")
{
	REQUIRE(Minimum(4, 3) == 3);
	REQUIRE(Minimum(3, 3) == 3);
	REQUIRE(Minimum(3, 4) == 3);
	REQUIRE(Minimum(3, -4) == -4);
	REQUIRE(Minimum(-3, -4) == -4);
	REQUIRE(Minimum(-3, 4) == -3);
}

TEST_CASE("ionComparsion::Maximum2", "maximum of two operands")
{
	REQUIRE(Maximum(4, 3) == 4);
	REQUIRE(Maximum(3, 3) == 3);
	REQUIRE(Maximum(3, 4) == 4);
	REQUIRE(Maximum(3, -4) == 3);
	REQUIRE(Maximum(-3, -4) == -3);
	REQUIRE(Maximum(-3, 4) == 4);
}

TEST_CASE("ionComparsion::MinMax3", "minimum/maximum of three operands")
{
	REQUIRE(Maximum(4, 3, 2) == 4);
	REQUIRE(Maximum(3, 3, 2) == 3);
	REQUIRE(Maximum(3, 2, 4) == 4);
	REQUIRE(Maximum(-5, 3, -4) == 3);
	REQUIRE(Maximum(-2, -3, -4) == -2);
	REQUIRE(Maximum(-3, 2, 4) == 4);

	REQUIRE(Minimum(4, 3, 2) == 2);
	REQUIRE(Minimum(3, 3, 2) == 2);
	REQUIRE(Minimum(3, 2, 4) == 2);
	REQUIRE(Minimum(-5, 3, -4) == -5);
	REQUIRE(Minimum(-2, -3, -4) == -4);
	REQUIRE(Minimum(-3, 2, 4) == -3);
}
