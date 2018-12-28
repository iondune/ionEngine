
#pragma once

#include "ionTypes.h"


namespace ion
{

	//! \ingroup ionCore
	//! \brief Tools for bitwise operations.
	class Bitwise
	{

	public:

		//! \brief Converts a vector of 0 or 1 bits to binary representation
		static uint BitsToByte(vector<uint> const & bits);

		//! \brief Extract the bits of a byte to a vector of 0 or 1 values
		//! Note that only the first 8 bits of Byte are examined
		static vector<uint> ByteToBits(uint const Byte);

		//! \brief Counts the number of set bits
		static uint BitCount(uint i);

	};

}
