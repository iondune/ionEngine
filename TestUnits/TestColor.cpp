
#include <ionCore/Color.h>
#include <catch.hpp>

using namespace ion;

TEST_CASE("Color::Hex")
{
	CHECK(Color::Hex(0xff6666) == color3i(255, 102, 102));
	CHECK(Color::Hex(0xFF0000) == color3i(255, 0, 0));
	CHECK(Color::Hex(0x33EEEE) == color3i(51, 238, 238));
}
