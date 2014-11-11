
#include <ionCore.h>
#include <catch.hpp>


class A
{};

TEST_CASE("sharedNew", "sharedNew allocates a new object")
{
	REQUIRE(sharedNew<A>(new A));
}
