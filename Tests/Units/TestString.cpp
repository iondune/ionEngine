
#include <ionCore.h>
#include <doctest.h>

using namespace ion;


TEST_CASE("ionContainer::String::SeparateLines")
{
	CHECK(String::SeparateLines("") == vector<string>());
	CHECK(String::SeparateLines("asdf") == vector<string>({ "asdf" }));
	CHECK(String::SeparateLines("a\nb\nc\n") == vector<string>({ "a", "b", "c" }));
	CHECK(String::SeparateLines("a\nb\nc") == vector<string>({ "a", "b", "c" }));
	CHECK(String::SeparateLines("abc\n123\nqwe") == vector<string>({ "abc", "123", "qwe" }));
}

TEST_CASE("ionContainer::String::Build")
{
	CHECK(String::Build("") == string());
	CHECK(String::Build("Test") == "Test");
	CHECK(String::Build("Hello %d", 123) == "Hello 123");
	CHECK(String::Build("%c %d %X %s", 'a', 42, 0xABCD, "foo") == "a 42 ABCD foo");
}

TEST_CASE("ionContainer::String::Explode")
{
	CHECK(String::Explode("", ' ') == vector<string>());
	CHECK(String::Explode("foo", ' ') == vector<string>({ "foo" }));
	CHECK(String::Explode("foo bar", ' ') == vector<string>({ "foo", "bar" }));
	CHECK(String::Explode("1,2,3", ',') == vector<string>({ "1", "2", "3" }));
	CHECK(String::Explode("1,2,", ',') == vector<string>({ "1", "2" }));
}

TEST_CASE("ionContainer::String::BeginsWith")
{
	string remainder;
	CHECK(String::BeginsWith("abc123", "abc", remainder));
	CHECK(remainder == "123");
	CHECK(String::BeginsWith("abc", "abc", remainder));
	CHECK(! String::BeginsWith("ab", "abc", remainder));
	CHECK(! String::BeginsWith("", "abc", remainder));
	CHECK(String::BeginsWith("abc", "", remainder));
	CHECK(remainder == "abc");
}
