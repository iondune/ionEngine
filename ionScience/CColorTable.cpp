#include "CColorTable.h"

#include "DefaultColorTable.h"


namespace ion
{

	CColorTable::CColorTable()
	{
		for (uint i = 0; i < DefaultColorTableCount; ++ i)
		{
			Colors.push_back(color3i(DefaultColorTable[i][0], DefaultColorTable[i][1], DefaultColorTable[i][2]));
		}
	}

	color3i const & CColorTable::Get(float const Value)
	{
		if (! Colors.size())
		{
			static color3i const NoColorsAvailable;
			return NoColorsAvailable;
		}

		return Colors[Clamp((uint) (Value * Colors.size()), 0u, (uint) Colors.size() - 1)];
	}

}
