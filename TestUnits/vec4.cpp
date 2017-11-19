
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("vec4 swizzle constructors")
{
	vec4i v;

	v = vec4i(vec3i(1, 2, 3), 4);
	CHECK(v.X == 1);
	CHECK(v.Y == 2);
	CHECK(v.Z == 3);
	CHECK(v.W == 4);

	v = vec4i(5, vec3i(6, 7, 8));
	CHECK(v.X == 5);
	CHECK(v.Y == 6);
	CHECK(v.Z == 7);
	CHECK(v.W == 8);

	v = vec4i(vec2i(9, 10), 11, 12);
	CHECK(v.X == 9);
	CHECK(v.Y == 10);
	CHECK(v.Z == 11);
	CHECK(v.W == 12);

	v = vec4i(13, vec2i(14, 15), 16);
	CHECK(v.X == 13);
	CHECK(v.Y == 14);
	CHECK(v.Z == 15);
	CHECK(v.W == 16);

	v = vec4i(17, 18, vec2i(19, 20));
	CHECK(v.X == 17);
	CHECK(v.Y == 18);
	CHECK(v.Z == 19);
	CHECK(v.W == 20);

	v = vec4i(vec2i(21, 22), vec2i(23, 24));
	CHECK(v.X == 21);
	CHECK(v.Y == 22);
	CHECK(v.Z == 23);
	CHECK(v.W == 24);
}
