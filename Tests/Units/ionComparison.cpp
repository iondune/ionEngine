
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("ionComparison::RoundingError", "rounding error constants")
{
	CHECK(RoundingError<int>::Value() == 0);
	CHECK(RoundingError<uint>::Value() == 0);
	CHECK(RoundingError<float>::Value() == RoundingError32);
	CHECK(RoundingError<double>::Value() == RoundingError64);
}

TEST_CASE("ionComparison::Equals<T>", "equality function")
{
	CHECK(Equals(0, 0));
	CHECK(Equals(1, 1));
	CHECK(Equals(-1, -1));

	CHECK(! Equals(0, 1));
	CHECK(! Equals(-1, 1));

	CHECK(Equals(0u, 0u));
	CHECK(Equals(0.f, RoundingError32));
	CHECK(! Equals(0.f, 1.5f * RoundingError32));
	CHECK(Equals(0.0, RoundingError64));
	CHECK(! Equals(0.0, 1.5 * RoundingError64));
}

TEST_CASE("ionComparsion::Minimum2", "minimum of two operands")
{
	CHECK(Minimum(4, 3) == 3);
	CHECK(Minimum(3, 3) == 3);
	CHECK(Minimum(3, 4) == 3);
	CHECK(Minimum(3, -4) == -4);
	CHECK(Minimum(-3, -4) == -4);
	CHECK(Minimum(-3, 4) == -3);
	CHECK(Min(4, 3) == 3);
	CHECK(Min(3, 3) == 3);
	CHECK(Min(3, 4) == 3);
	CHECK(Min(3, -4) == -4);
	CHECK(Min(-3, -4) == -4);
	CHECK(Min(-3, 4) == -3);
}

TEST_CASE("ionComparsion::Maximum2", "maximum of two operands")
{
	CHECK(Maximum(4, 3) == 4);
	CHECK(Maximum(3, 3) == 3);
	CHECK(Maximum(3, 4) == 4);
	CHECK(Maximum(3, -4) == 3);
	CHECK(Maximum(-3, -4) == -3);
	CHECK(Maximum(-3, 4) == 4);
	CHECK(Max(4, 3) == 4);
	CHECK(Max(3, 3) == 3);
	CHECK(Max(3, 4) == 4);
	CHECK(Max(3, -4) == 3);
	CHECK(Max(-3, -4) == -3);
	CHECK(Max(-3, 4) == 4);
}

TEST_CASE("ionComparsion::MinMax3", "minimum/maximum of three operands")
{
	CHECK(Maximum(4, 3, 2) == 4);
	CHECK(Maximum(3, 3, 2) == 3);
	CHECK(Maximum(3, 2, 4) == 4);
	CHECK(Maximum(-5, 3, -4) == 3);
	CHECK(Maximum(-2, -3, -4) == -2);
	CHECK(Maximum(-3, 2, 4) == 4);

	CHECK(Minimum(4, 3, 2) == 2);
	CHECK(Minimum(3, 3, 2) == 2);
	CHECK(Minimum(3, 2, 4) == 2);
	CHECK(Minimum(-5, 3, -4) == -5);
	CHECK(Minimum(-2, -3, -4) == -4);
	CHECK(Minimum(-3, 2, 4) == -3);

	CHECK(Max(4, 3, 2) == 4);
	CHECK(Max(3, 3, 2) == 3);
	CHECK(Max(3, 2, 4) == 4);
	CHECK(Max(-5, 3, -4) == 3);
	CHECK(Max(-2, -3, -4) == -2);
	CHECK(Max(-3, 2, 4) == 4);

	CHECK(Min(4, 3, 2) == 2);
	CHECK(Min(3, 3, 2) == 2);
	CHECK(Min(3, 2, 4) == 2);
	CHECK(Min(-5, 3, -4) == -5);
	CHECK(Min(-2, -3, -4) == -4);
	CHECK(Min(-3, 2, 4) == -3);
}

TEST_CASE("ionComparsion::MinMax4", "minimum/maximum of four operands")
{
	CHECK(Maximum(4, 3, 2, 1) == 4);
	CHECK(Maximum(3, 3, 2, 1) == 3);
	CHECK(Maximum(3, 2, 4, -1) == 4);
	CHECK(Maximum(-5, 3, -4, -6) == 3);
	CHECK(Maximum(-2, -3, -4, -2) == -2);
	CHECK(Maximum(-3, 2, 4, 5) == 5);

	CHECK(Minimum(4, 3, 2, 2) == 2);
	CHECK(Minimum(3, 3, 2, 1) == 1);
	CHECK(Minimum(3, 2, 4, 5) == 2);
	CHECK(Minimum(-5, 3, -4, -3) == -5);
	CHECK(Minimum(-2, -3, -4, -1) == -4);
	CHECK(Minimum(-3, 2, 4, 1) == -3);

	CHECK(Max(4, 3, 2, 1) == 4);
	CHECK(Max(3, 3, 2, 1) == 3);
	CHECK(Max(3, 2, 4, -1) == 4);
	CHECK(Max(-5, 3, -4, -6) == 3);
	CHECK(Max(-2, -3, -4, -2) == -2);
	CHECK(Max(-3, 2, 4, 5) == 5);

	CHECK(Min(4, 3, 2, 2) == 2);
	CHECK(Min(3, 3, 2, 1) == 1);
	CHECK(Min(3, 2, 4, 5) == 2);
	CHECK(Min(-5, 3, -4, -3) == -5);
	CHECK(Min(-2, -3, -4, -1) == -4);
	CHECK(Min(-3, 2, 4, 1) == -3);
}
