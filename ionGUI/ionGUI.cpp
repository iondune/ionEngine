
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

bool ImGui::ColorEdit3(const char * label, color3f & Color)
{
	float c[3] = { Color.Red, Color.Green, Color.Blue };
	if (ImGui::ColorEdit3(label, c))
	{
		Color = color3f(c[0], c[1], c[2]);
		return true;
	}
	return false;
}

bool ImGui::DragVec3(const char * label, vec3f & v, float v_speed, float v_min, float v_max, const char * display_format, float power)
{
	float vals[3] = { v.X, v.Y, v.Z };
	if (ImGui::DragFloat3(label, vals, v_speed, v_min, v_max, display_format, power))
	{
		v = vec3f(vals[0], vals[1], vals[2]);
		return true;
	}
	return false;
}

char const * ion::BoolToString(bool const B)
{
	return B ? "yes" : "no";
}
