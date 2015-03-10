
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

TEST_CASE("ionStandardLibrary::ConditionalUnorderedMapAccess")
{
	unordered_map<int, int *> Test;
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

TEST_CASE("ionStandardLibrary::CheckMapAccess")
{
	map<int, int *> Test;
	REQUIRE(! CheckMapAccess(Test, 0));
	REQUIRE(! CheckMapAccess(Test, 1));
	REQUIRE(! CheckMapAccess(Test, 2));

	int X, Y;

	Test[0] = & X;
	Test[1] = & Y;
	Test[2] = & Y;
	Test[3] = nullptr;
	REQUIRE(! CheckMapAccess(Test, -1));
	REQUIRE(CheckMapAccess(Test, 0));
	REQUIRE(CheckMapAccess(Test, 1));
	REQUIRE(CheckMapAccess(Test, 2));
	REQUIRE(CheckMapAccess(Test, 3));
	REQUIRE(! CheckMapAccess(Test, 4));
}

TEST_CASE("ionStandardLibrary::TryMapAccess")
{
	map<int, int> Map;
	int X = -1;
	
	REQUIRE(! TryMapAccess(Map, 0, X));
	REQUIRE(X == -1);
	REQUIRE(! TryMapAccess(Map, 1, X));
	REQUIRE(X == -1);

	Map[0] = 2;

	REQUIRE(TryMapAccess(Map, 0, X));
	REQUIRE(X == 2);
	X = -1;
	REQUIRE(! TryMapAccess(Map, 1, X));
	REQUIRE(X == -1);
}

TEST_CASE("ionStandardLibrary::KeySet")
{
	map<int, int> Map;

	REQUIRE(KeySet(Map) == set<int>());
	Map[0] = 0;
	REQUIRE(KeySet(Map) == set<int>({0}));
	Map[1] = 'a';
	REQUIRE(KeySet(Map) == set<int>({0, 1}));
	Map[2] = 'b';
	REQUIRE(KeySet(Map) == set<int>({0, 1, 2}));
}

TEST_CASE("ionStandardLibrary::AddAtEnd")
{
	vector<int> A, B;

	AddAtEnd(A, B);
	REQUIRE(A == vector<int>());
	REQUIRE(B == vector<int>());

	A.push_back(1);
	AddAtEnd(A, B);
	REQUIRE(A == vector<int>({1}));
	REQUIRE(B == vector<int>());

	A.push_back(2);
	AddAtEnd(A, B);
	REQUIRE(A == vector<int>({1, 2}));
	REQUIRE(B == vector<int>());

	B.push_back(3);
	AddAtEnd(A, B);
	REQUIRE(A == vector<int>({1, 2, 3}));
	REQUIRE(B == vector<int>({3}));

	B.push_back(4);
	AddAtEnd(A, B);
	REQUIRE(A == vector<int>({1, 2, 3, 3, 4}));
	REQUIRE(B == vector<int>({3, 4}));
}

TEST_CASE("ionStandardLibrary::String::SeparateLines")
{
	REQUIRE(String::SeparateLines("") == vector<string>());
	REQUIRE(String::SeparateLines("asdf") == vector<string>({"asdf"}));
	REQUIRE(String::SeparateLines("a\nb\nc\n") == vector<string>({"a", "b", "c"}));
	REQUIRE(String::SeparateLines("a\nb\nc") == vector<string>({"a", "b", "c"}));
	REQUIRE(String::SeparateLines("abc\n123\nqwe") == vector<string>({"abc", "123", "qwe"}));
}

TEST_CASE("ionStandardLibrary::String::Build")
{
	REQUIRE(String::Build("") == string());
	REQUIRE(String::Build("Test") == "Test");
	REQUIRE(String::Build("Hello %d", 123) == "Hello 123");
	REQUIRE(String::Build("%c %d %X %s", 'a', 42, 0xABCD, "foo") == "a 42 ABCD foo");
}

TEST_CASE("ionStandardLibrary::String::Explode")
{
	REQUIRE(String::Explode("", ' ') == vector<string>());
	REQUIRE(String::Explode("foo", ' ') == vector<string>({"foo"}));
	REQUIRE(String::Explode("foo bar", ' ') == vector<string>({"foo", "bar"}));
	REQUIRE(String::Explode("1,2,3", ',') == vector<string>({"1", "2", "3"}));
	REQUIRE(String::Explode("1,2,", ',') == vector<string>({"1", "2"}));
}
