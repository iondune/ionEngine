
#pragma once

#include "ionTypes.h"


namespace ion
{

	class Bitwise
	{

	public:

		static uint BitsToByte(vector<uint> const & bits)
		{
			uint Byte = 0;
			for (auto bit : bits)
			{
				Byte |= 1 << bit;
			}

			return Byte;
		}

		static vector<uint> ByteToBits(uint const Byte)
		{
			vector<uint> Bits;

			for (uint i = 0; i < 8; ++i)
			{
				if (Byte & (1 << i))
				{
					Bits.push_back(i);
				}
			}

			return Bits;
		}

		static uint BitCount(uint i)
		{
			i = i - ((i >> 1) & 0x55555555);
			i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
			return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
		}

	};

}
