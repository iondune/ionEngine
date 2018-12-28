
#pragma once

#include <ionMath.h>
#include <vector>


namespace ion
{

	class CColorTable
	{

		vector<color3i> Colors;

	public:

		CColorTable();

		color3i const & Get(float const Value);

	};

}
