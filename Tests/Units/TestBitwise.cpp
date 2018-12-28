
#include <ionCore.h>
#include <catch.hpp>

using namespace ion;


TEST_CASE("Bitwise::ByteToBits", "")
{
	CHECK(Bitwise::ByteToBits(0x00) == vector<uint>({}));
	CHECK(Bitwise::ByteToBits(0x01) == vector<uint>({ 0 }));
	CHECK(Bitwise::ByteToBits(0x02) == vector<uint>({ 1 }));
	CHECK(Bitwise::ByteToBits(0x03) == vector<uint>({ 0, 1 }));
	CHECK(Bitwise::ByteToBits(0x04) == vector<uint>({ 2 }));
	CHECK(Bitwise::ByteToBits(0x05) == vector<uint>({ 0, 2 }));
	CHECK(Bitwise::ByteToBits(0x06) == vector<uint>({ 1, 2 }));
	CHECK(Bitwise::ByteToBits(0x07) == vector<uint>({ 0, 1, 2 }));
	CHECK(Bitwise::ByteToBits(0x08) == vector<uint>({ 3 }));
	CHECK(Bitwise::ByteToBits(0x09) == vector<uint>({ 0, 3 }));
	CHECK(Bitwise::ByteToBits(0xFF) == vector<uint>({ 0, 1, 2, 3, 4, 5, 6, 7 }));
}

TEST_CASE("Bitwise::BitsToByte", "")
{
	CHECK(Bitwise::BitsToByte({}) == 0x00);
	CHECK(Bitwise::BitsToByte({ 0 }) == 0x01);
	CHECK(Bitwise::BitsToByte({ 1 }) == 0x02);
	CHECK(Bitwise::BitsToByte({ 0, 1 }) == 0x03);
	CHECK(Bitwise::BitsToByte({ 0, 1, 2, 3 }) == 0x0F);
	CHECK(Bitwise::BitsToByte({ 0, 1, 2, 3, 4, 5, 6, 7 }) == 0xFF);
}

TEST_CASE("Bitwise::BitCount", "")
{
	CHECK(Bitwise::BitCount(0x00) == 0);
	CHECK(Bitwise::BitCount(0x01) == 1);
	CHECK(Bitwise::BitCount(0x02) == 1);
	CHECK(Bitwise::BitCount(0x03) == 2);
	CHECK(Bitwise::BitCount(0x04) == 1);
	CHECK(Bitwise::BitCount(0x05) == 2);
	CHECK(Bitwise::BitCount(0x06) == 2);
	CHECK(Bitwise::BitCount(0x07) == 3);
	CHECK(Bitwise::BitCount(0x08) == 1);
	CHECK(Bitwise::BitCount(0x10) == 1);
	CHECK(Bitwise::BitCount(0xF0) == 4);
	CHECK(Bitwise::BitCount(0xFF) == 8);
}
