
#include <ionCore/Color.h>
#include <doctest.h>

using namespace ion;

TEST_CASE("Color::Hex")
{
	CHECK(Color::Hex(0xff6666) == color3i(255, 102, 102));
	CHECK(Color::Hex(0xFF0000) == color3i(255, 0, 0));
	CHECK(Color::Hex(0x33EEEE) == color3i(51, 238, 238));

	CHECK(Color::Hex("33EE66") == color3i(51, 238, 102));
	CHECK(Color::Hex("#33EE66") == color3i(51, 238, 102));
	// CHECK(Color::Hex("#fff") == color3i(255, 255, 255));
	// CHECK(Color::Hex("#000") == color3i(0, 0, 0));
	// CHECK(Color::Hex("#111") == color3i(16, 16, 16));
}

TEST_CASE("Color::HSV")
{
	CHECK(Color::HSV(0.f, 0.f, 0.f) == color3f(0, 0, 0));
	CHECK(Color::HSV(0.f, 0.f, 1.f) == color3f(1, 1, 1));
	CHECK(Color::HSV(0.f, 1.f, 1.f) == color3f(1, 0, 0));

	CHECK(Color::HSV(1.f / 6.f, 1.f, 1.f) == color3f(1, 1, 0));
	CHECK(Color::HSV(1.f / 3.f, 1.f, 1.f) == color3f(0, 1, 0));
	CHECK(Color::HSV(1.f / 2.f, 1.f, 1.f) == color3f(0, 1, 1));
	CHECK(Color::HSV(2.f / 3.f, 1.f, 1.f) == color3f(0, 0, 1));
	CHECK(Color::HSV(5.f / 6.f, 1.f, 1.f) == color3f(1, 0, 1));
}

TEST_CASE("Color::ToHSV")
{
	CHECK(Color::ToHSV(color3f(0, 0, 0)) == vec3f(0.f, 0.f, 0.f));
	CHECK(Color::ToHSV(color3f(1, 1, 1)) == vec3f(0.f, 0.f, 1.f));
	CHECK(Color::ToHSV(color3f(1, 0, 0)) == vec3f(0.f, 1.f, 1.f));

	CHECK(Color::ToHSV(color3f(1, 1, 0)) == vec3f(1.f / 6.f, 1.f, 1.f));
	CHECK(Color::ToHSV(color3f(0, 1, 0)) == vec3f(1.f / 3.f, 1.f, 1.f));
	CHECK(Color::ToHSV(color3f(0, 1, 1)) == vec3f(1.f / 2.f, 1.f, 1.f));
	CHECK(Color::ToHSV(color3f(0, 0, 1)) == vec3f(2.f / 3.f, 1.f, 1.f));
	CHECK(Color::ToHSV(color3f(1, 0, 1)) == vec3f(5.f / 6.f, 1.f, 1.f));
}
