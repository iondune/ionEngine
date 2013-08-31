#include "CColorTable.h"

#include "DefaultColorTable.h"


CColorTable::CColorTable()
{
	for (u32 i = 0; i < DefaultColorTableCount; ++ i)
	{
		Colors.push_back(color3i(DefaultColorTable[i][0], DefaultColorTable[i][1], DefaultColorTable[i][2]));
	}
}

color3i const & CColorTable::Get(f32 const Value)
{
	if (! Colors.size())
	{
		static color3i const NoColorsAvailable;
		return NoColorsAvailable;
	}

	return Colors[Clamp((u32) (Value * Colors.size()), 0u, Colors.size() - 1)];
}
