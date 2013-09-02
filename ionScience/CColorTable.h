
#pragma once

#include <ionMath.h>
#include <vector>


class CColorTable
{

	std::vector<color3i> Colors;

public:

	CColorTable();

	color3i const & Get(f32 const Value);

};
