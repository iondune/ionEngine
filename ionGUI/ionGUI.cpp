#include "ionGUI.h"

bool ImGui::SliderDouble(const char * label, double * v, double v_min, double v_max, const char * display_format, double power)
{
	float temp = (float) *v;
	if (SliderFloat(label, &temp, (float) v_min, (float) v_max, display_format, (float) power))
	{
		*v = (double) temp;
		return true;
	}
	else
	{
		return false;
	}
}
