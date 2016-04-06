
#include <ionCore.h>
#include <catch.hpp>


TEST_CASE("ionStandardLibrary::ConditionalMapAccess")
{
	map<int, int *> Test;
	CHECK(! ConditionalMapAccess(Test, 0));
	CHECK(! ConditionalMapAccess(Test, 1));
	CHECK(! ConditionalMapAccess(Test, 2));

	int X, Y;

	Test[0] = & X;
	Test[1] = & Y;
	Test[2] = & Y;
	CHECK(! ConditionalMapAccess(Test, -1));
	CHECK(& X == ConditionalMapAccess(Test, 0));
	CHECK(& Y == ConditionalMapAccess(Test, 1));
	CHECK(& Y == ConditionalMapAccess(Test, 2));
	CHECK(! ConditionalMapAccess(Test, 3));
	CHECK(! ConditionalMapAccess(Test, 4));
}

TEST_CASE("ionStandardLibrary::ConditionalUnorderedMapAccess")
{
	unordered_map<int, int *> Test;
	CHECK(! ConditionalMapAccess(Test, 0));
	CHECK(! ConditionalMapAccess(Test, 1));
	CHECK(! ConditionalMapAccess(Test, 2));

	int X, Y;

	Test[0] = & X;
	Test[1] = & Y;
	Test[2] = & Y;
	CHECK(! ConditionalMapAccess(Test, -1));
	CHECK(& X == ConditionalMapAccess(Test, 0));
	CHECK(& Y == ConditionalMapAccess(Test, 1));
	CHECK(& Y == ConditionalMapAccess(Test, 2));
	CHECK(! ConditionalMapAccess(Test, 3));
	CHECK(! ConditionalMapAccess(Test, 4));
}

TEST_CASE("ionStandardLibrary::CheckMapAccess")
{
	map<int, int *> Test;
	CHECK(! CheckMapAccess(Test, 0));
	CHECK(! CheckMapAccess(Test, 1));
	CHECK(! CheckMapAccess(Test, 2));

	int X, Y;

	Test[0] = & X;
	Test[1] = & Y;
	Test[2] = & Y;
	Test[3] = nullptr;
	CHECK(! CheckMapAccess(Test, -1));
	CHECK(CheckMapAccess(Test, 0));
	CHECK(CheckMapAccess(Test, 1));
	CHECK(CheckMapAccess(Test, 2));
	CHECK(CheckMapAccess(Test, 3));
	CHECK(! CheckMapAccess(Test, 4));
}

TEST_CASE("ionStandardLibrary::TryMapAccess")
{
	map<int, int> Map;
	int X = -1;

	CHECK(! TryMapAccess(Map, 0, X));
	CHECK(X == -1);
	CHECK(! TryMapAccess(Map, 1, X));
	CHECK(X == -1);

	Map[0] = 2;

	CHECK(TryMapAccess(Map, 0, X));
	CHECK(X == 2);
	X = -1;
	CHECK(! TryMapAccess(Map, 1, X));
	CHECK(X == -1);
}

TEST_CASE("ionStandardLibrary::KeySet")
{
	map<int, int> Map;

	CHECK(KeySet(Map) == set<int>());
	Map[0] = 0;
	CHECK(KeySet(Map) == set<int>({0}));
	Map[1] = 'a';
	CHECK(KeySet(Map) == set<int>({0, 1}));
	Map[2] = 'b';
	CHECK(KeySet(Map) == set<int>({0, 1, 2}));
}

TEST_CASE("ionStandardLibrary::AddAtEnd")
{
	vector<int> A, B;

	AddAtEnd(A, B);
	CHECK(A == vector<int>());
	CHECK(B == vector<int>());

	A.push_back(1);
	AddAtEnd(A, B);
	CHECK(A == vector<int>({1}));
	CHECK(B == vector<int>());

	A.push_back(2);
	AddAtEnd(A, B);
	CHECK(A == vector<int>({1, 2}));
	CHECK(B == vector<int>());

	B.push_back(3);
	AddAtEnd(A, B);
	CHECK(A == vector<int>({1, 2, 3}));
	CHECK(B == vector<int>({3}));

	B.push_back(4);
	AddAtEnd(A, B);
	CHECK(A == vector<int>({1, 2, 3, 3, 4}));
	CHECK(B == vector<int>({3, 4}));
}

TEST_CASE("ionStandardLibrary::File::StripExtension")
{
	CHECK(File::StripExtension("") == "");
	CHECK(File::StripExtension("a") == "a");
	CHECK(File::StripExtension("File.ext") == "File");
	CHECK(File::StripExtension("File.extension") == "File");
	CHECK(File::StripExtension("File.with.extension") == "File");
}

TEST_CASE("ionStandardLibrary::File::GetExtension")
{
	CHECK(File::GetExtension("") == "");
	CHECK(File::GetExtension("a") == "");
	CHECK(File::GetExtension("File.ext") == "ext");
	CHECK(File::GetExtension("File.extension") == "extension");
	CHECK(File::GetExtension("File.with.extension") == "extension");
}

TEST_CASE("ionStandardLibrary::String::SeparateLines")
{
	CHECK(String::SeparateLines("") == vector<string>());
	CHECK(String::SeparateLines("asdf") == vector<string>({"asdf"}));
	CHECK(String::SeparateLines("a\nb\nc\n") == vector<string>({"a", "b", "c"}));
	CHECK(String::SeparateLines("a\nb\nc") == vector<string>({"a", "b", "c"}));
	CHECK(String::SeparateLines("abc\n123\nqwe") == vector<string>({"abc", "123", "qwe"}));
}

TEST_CASE("ionStandardLibrary::String::Build")
{
	CHECK(String::Build("") == string());
	CHECK(String::Build("Test") == "Test");
	CHECK(String::Build("Hello %d", 123) == "Hello 123");
	CHECK(String::Build("%c %d %X %s", 'a', 42, 0xABCD, "foo") == "a 42 ABCD foo");
}

TEST_CASE("ionStandardLibrary::String::Explode")
{
	CHECK(String::Explode("", ' ') == vector<string>());
	CHECK(String::Explode("foo", ' ') == vector<string>({"foo"}));
	CHECK(String::Explode("foo bar", ' ') == vector<string>({"foo", "bar"}));
	CHECK(String::Explode("1,2,3", ',') == vector<string>({"1", "2", "3"}));
	CHECK(String::Explode("1,2,", ',') == vector<string>({"1", "2"}));
}
