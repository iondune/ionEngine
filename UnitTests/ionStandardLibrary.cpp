
#include <ionCore.h>
#include <catch.hpp>


TEST_CASE("ionStandardLibrary::ConditionalMapAccess")
{
	map<int, int *> Test;
	REQUIRE(! ConditionalMapAccess(Test, 0));
	REQUIRE(! ConditionalMapAccess(Test, 1));
	REQUIRE(! ConditionalMapAccess(Test, 2));

	int X, Y;

	Test[0] = & X;
	Test[1] = & Y;
	Test[2] = & Y;
	REQUIRE(! ConditionalMapAccess(Test, -1));
	REQUIRE(& X == ConditionalMapAccess(Test, 0));
	REQUIRE(& Y == ConditionalMapAccess(Test, 1));
	REQUIRE(& Y == ConditionalMapAccess(Test, 2));
	REQUIRE(! ConditionalMapAccess(Test, 3));
	REQUIRE(! ConditionalMapAccess(Test, 4));
}

TEST_CASE("ionStandardLibrary::String::Build")
{
	REQUIRE(String::Build("") == string());
	REQUIRE(String::Build("Test") == "Test");
	REQUIRE(String::Build("Hello %d", 123) == "Hello 123");
	REQUIRE(String::Build("%c %d %X %s", 'a', 42, 0xABCD, "foo") == "a 42 ABCD foo");
}
