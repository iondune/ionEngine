
#pragma once

#include <ionConfig.h>
#include "CGUIManager.h"
#include "CWindowWidget.h"


namespace ImGui
{
	bool SliderDouble(const char* label, double* v, double v_min, double v_max, const char* display_format = "%.3f", double power = 1.0);
	bool ColorEdit3(const char* label, color3f & Color);
}
