
#include <ionCore.h>
#include <catch.hpp>


TEST_CASE("Bitwise::ByteToBits", "")
{
	CHECK(ion::Bitwise::ByteToBits(0x00) == vector<uint>({}));
	CHECK(ion::Bitwise::ByteToBits(0x01) == vector<uint>({ 0 }));
	CHECK(ion::Bitwise::ByteToBits(0x02) == vector<uint>({ 1 }));
	CHECK(ion::Bitwise::ByteToBits(0x03) == vector<uint>({ 0, 1 }));
	CHECK(ion::Bitwise::ByteToBits(0x04) == vector<uint>({ 2 }));
	CHECK(ion::Bitwise::ByteToBits(0x05) == vector<uint>({ 0, 2 }));
	CHECK(ion::Bitwise::ByteToBits(0x06) == vector<uint>({ 1, 2 }));
	CHECK(ion::Bitwise::ByteToBits(0x07) == vector<uint>({ 0, 1, 2 }));
	CHECK(ion::Bitwise::ByteToBits(0x08) == vector<uint>({ 3 }));
	CHECK(ion::Bitwise::ByteToBits(0x09) == vector<uint>({ 0, 3 }));
	CHECK(ion::Bitwise::ByteToBits(0xFF) == vector<uint>({ 0, 1, 2, 3, 4, 5, 6, 7 }));
}

TEST_CASE("Bitwise::BitsToByte", "")
{
	CHECK(ion::Bitwise::BitsToByte({}) == 0x00);
}
