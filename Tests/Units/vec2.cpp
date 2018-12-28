
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("vec2 constructors")
{
	vec2i a(1, 2);
	CHECK(a.X == 1);
	CHECK(a.Y == 2);

	vec2i b(a);
	CHECK(b.X == 1);
	CHECK(b.Y == 2);

	vec2i c(5);
	CHECK(c.X == 5);
	CHECK(c.Y == 5);

	vec2i d(vec2f(6.f, 8.f));
	CHECK(d.X == 6);
	CHECK(d.Y == 8);

	vec2i e(glm::ivec2(9, 10));
	CHECK(e.X == 9);
	CHECK(e.Y == 10);
}

TEST_CASE("vec2::operator[]")
{
	vec2i const a(3, 5);
	CHECK(a[-1] == 0);
	CHECK(a[0] == 3);
	CHECK(a[1] == 5);
	CHECK(a[2] == 0);

	vec2i b(6, 7);
	CHECK(b[-1] == 0);
	CHECK(b[0] == 6);
	CHECK(b[1] == 7);
	CHECK(b[2] == 0);

	b[-1] = 9;
	b[0] = 10;
	b[1] = 11;
	b[2] = 12;

	CHECK(b[-1] == 0);
	CHECK(b[0] == 10);
	CHECK(b[1] == 11);
	CHECK(b[2] == 0);
}

TEST_CASE("vec2::operator =")
{
	vec2i a, b, c, d, e;

	a = vec2i(1, 2);
	CHECK(a.X == 1);
	CHECK(a.Y == 2);

	b = a;
	CHECK(b.X == 1);
	CHECK(b.Y == 2);

	c = 5;
	CHECK(c.X == 5);
	CHECK(c.Y == 5);

	d = vec2f(6.f, 8.f);
	CHECK(d.X == 6);
	CHECK(d.Y == 8);

	e = glm::ivec2(9, 10);
	CHECK(e.X == 9);
	CHECK(e.Y == 10);
}

TEST_CASE("vec2 basic arithmetic")
{
	vec2i a(1, 2), b(3, 6), c, d, e;

	c = a + b;
	CHECK(c.X == 4);
	CHECK(c.Y == 8);

	c = a - b;
	CHECK(c.X == -2);
	CHECK(c.Y == -4);
}

TEST_CASE("vec2::operator <")
{
	CHECK(vec2i(-1, -1) < vec2i(0, -1));
	CHECK(! (vec2i(0, 0) < vec2i(0, 0)));
	CHECK(! (vec2i(2, 2) < vec2i(2, 2)));
	CHECK(! (vec2i(-2, 2) < vec2i(-2, 2)));
	CHECK(! (vec2i(2, -2) < vec2i(2, -2)));

	CHECK(vec2i(-4, -4) < vec2i(-3, -10));
	CHECK(vec2i(-4, -4) < vec2i(-3, 10));
	CHECK(vec2i(-4, -4) < vec2i(-4, -3));
}

TEST_CASE("vec2 used as a map index (uses operator <)")
{
	map<vec2i, int> Map;
	Map[vec2i(-1, -1)] = 3;
	Map[vec2i(0, -1)] = 4;

	REQUIRE(Map.size() == 2);

	auto it = Map.begin();
	CHECK(it->first.X == -1);
	CHECK(it->first.Y == -1);
	CHECK(it->second == 3);
	it ++;
	CHECK(it->first.X == 0);
	CHECK(it->first.Y == -1);
	CHECK(it->second == 4);

	Map[vec2i(-1, -1)] = 5;
	CHECK(Map[vec2i(-1, -1)] == 5);
	Map[vec2i(1, 1)] = 7;
	CHECK(Map[vec2i(1, 1)] == 7);
	Map[vec2i(2, 1)] = 8;
	CHECK(Map[vec2i(2, 1)] == 8);
	Map[vec2i(1, 2)] = 9;
	CHECK(Map[vec2i(1, 2)] == 9);

	for (int t = -20; t <= 20; ++ t)
	{
		for (int q = -20; q <= 20; ++ q)
		{
			Map[vec2i(t, q)] = 13 + 50 * (t + 21) + (q + 21);
		}
	}
	for (int t = -20; t <= 20; ++ t)
	{
		for (int q = -20; q <= 20; ++ q)
		{
			CHECK(Map[vec2i(t, q)] == 13 + 50 * (t + 21) + (q + 21));
		}
	}
}
