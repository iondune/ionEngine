
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("ionContainer::ConditionalMapAccess")
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

TEST_CASE("ionContainer::ConditionalUnorderedMapAccess")
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

TEST_CASE("ionContainer::CheckMapAccess")
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

TEST_CASE("ionContainer::TryMapAccess")
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

TEST_CASE("ionContainer::KeySet")
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

TEST_CASE("ionContainer::AddAtEnd")
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
