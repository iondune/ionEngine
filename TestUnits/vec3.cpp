
#include <ionMath.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("vec3::vec3")
{
	vec3f v1 = vec3f();
	CHECK(v1.X == 0);
	CHECK(v1.X == 0);
	CHECK(v1.X == 0);

	vec3f v2 = vec3f(2);
	CHECK(v2.X == 2);
	CHECK(v2.Y == 2);
	CHECK(v2.Z == 2);

	vec3f v3 = vec3f(3, 4, 5);
	CHECK(v3.X == 3);
	CHECK(v3.Y == 4);
	CHECK(v3.Z == 5);
}

TEST_CASE("SVector3::operator <", "")
{
	CHECK(vec3i(-1, -1, 0) < vec3i(0, -1, 0));
	CHECK(! (vec3i(0, 0, 0) < vec3i(0, 0, 0)));
	CHECK(! (vec3i(2, 2, 0) < vec3i(2, 2, 0)));
	CHECK(! (vec3i(-2, 2, 0) < vec3i(-2, 2, 0)));
	CHECK(! (vec3i(2, -2, 0) < vec3i(2, -2, 0)));

	CHECK(vec3i(-4, -4, 0) < vec3i(-3, -10, 0));
	CHECK(vec3i(-4, -4, 0) < vec3i(-3, 10, 0));
	CHECK(vec3i(-4, -4, 0) < vec3i(-4, -3, 0));

	CHECK(vec3i(0, 0, 0) < vec3i(0, 0, 1));
	CHECK(vec3i(0, 0, 0) < vec3i(0, 1, 0));
	CHECK(vec3i(0, 0, 0) < vec3i(1, 0, 0));
	CHECK(vec3i(0, 0, -1) < vec3i(0, 0, 0));
	CHECK(! (vec3i(0, 0, 1) < vec3i(0, 0, 0)));
	CHECK(! (vec3i(0, 1, 0) < vec3i(0, 0, 0)));
	CHECK(! (vec3i(1, 0, 0) < vec3i(0, 0, 0)));
	CHECK(! (vec3i(0, 0, 0) < vec3i(0, 0, -1)));
}
