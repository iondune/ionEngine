
#pragma once

#include "ionTypes.h"

#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

using std::move;
using std::ifstream;

template <typename T, typename U>
U * ConditionalMapAccess(map<T, U *> & Map, T const Key)
{
	auto Iterator = Map.find(Key);

	if (Iterator != Map.end())
		return Iterator->second;

	return 0;
}
