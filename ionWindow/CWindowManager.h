
#pragma once

#include <ionMath.h>

#include "CWindow.h"


class CWindowManager
{

public:

	void Init();

	CWindow * CreateWindow(vec2i const & Size, std::string const & Title);

};
