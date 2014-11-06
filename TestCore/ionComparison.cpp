
#include <ionCore.h>
#include <catch.hpp>

TEST_CASE("ionComparison::Equals<T>", "equality function")
{
	REQUIRE(Equals(0, 0));
}

TEST_CASE("ionComparsion::Minimum2", "minimum of two operands")
{
	REQUIRE(Minimum(4, 3) == 3);
}
