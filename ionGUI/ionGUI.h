
#pragma once

#include <ionConfig.h>
#include "CGUIManager.h"
#include "CWindowWidget.h"


namespace ImGui
{
	bool SliderDouble(const char* label, double* v, double v_min, double v_max, const char* display_format = "%.3f", double power = 1.0);
	bool ColorEdit3(const char* label, color3f & Color);

	bool ColorPicker4(float* col, bool show_alpha);
	bool ColorPicker3(float col[3]);
	bool ColorPicker3(color3f & col);
}

namespace ion
{

	char const * BoolToString(bool const B);

}
