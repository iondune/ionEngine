
#include <ionCore.h>
#include <catch.hpp>


TEST_CASE("ionStandardLibrary::String::Build")
{
	REQUIRE(String::Build("") == string());
	REQUIRE(String::Build("Test") == "Test");
	REQUIRE(String::Build("Hello %d", 123) == "Hello 123");
	REQUIRE(String::Build("%c %d %X %s", 'a', 42, 0xABCD, "foo") == "a 42 ABCD foo");
}
