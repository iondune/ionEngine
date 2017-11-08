
#include "ionGUI.h"

using namespace ion;


namespace ImGui
{

	bool SliderDouble(const char * label, double * v, double v_min, double v_max, const char * display_format, double power)
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

	bool ColorEdit3(const char * label, color3f & Color)
	{
		float c[3] = { Color.Red, Color.Green, Color.Blue };
		if (ImGui::ColorEdit3(label, c))
		{
			Color = color3f(c[0], c[1], c[2]);
			return true;
		}
		return false;
	}

	bool DragVec2(const char * label, ion::vec2i & v, float v_speed, int v_min, int v_max, const char * display_format)
	{
		int vals[2] = { v.X, v.Y };
		if (ImGui::DragInt2(label, vals,  v_speed, v_min, v_max, display_format))
		{
			v = vec2i(vals[0], vals[1]);
			return true;
		}
		return false;
	}

	bool DragVec2(const char * label, vec2f & v, float v_speed, float v_min, float v_max, const char * display_format, float power)
	{
		float vals[2] = { v.X, v.Y };
		if (ImGui::DragFloat2(label, vals, v_speed, v_min, v_max, display_format, power))
		{
			v = vec2f(vals[0], vals[1]);
			return true;
		}
		return false;
	}

	bool DragVec3(const char * label, vec3f & v, float v_speed, float v_min, float v_max, const char * display_format, float power)
	{
		float vals[3] = { v.X, v.Y, v.Z };
		if (ImGui::DragFloat3(label, vals, v_speed, v_min, v_max, display_format, power))
		{
			v = vec3f(vals[0], vals[1], vals[2]);
			return true;
		}
		return false;
	}

	bool Combo(const char * label, int * current_item, std::initializer_list<char const *> const & items, int height_in_items)
	{
		vector<char const *> items_vec = items;
		return ImGui::Combo(label, current_item, items_vec.data(), (int) items.size(), height_in_items);
	}

	bool Combo(const char * label, int * current_item, std::vector<string> const & items, int height_in_items)
	{
		vector<char const *> items_vec;
		for (string const & item : items)
		{
			items_vec.push_back(item.c_str());
		}

		return ImGui::Combo(label, current_item, items_vec.data(), (int) items.size(), height_in_items);
	}

	bool InputText(const char * label, string & buf, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void * user_data)
	{
		static vector<char> buffer_copy;
		static int const ReserveSpace = 32;

		if (buffer_copy.size() < buf.size() + ReserveSpace)
		{
			buffer_copy.resize(buf.size() + ReserveSpace);
		}

		strcpy(buffer_copy.data(), buf.c_str());

		if (ImGui::InputText(label, buffer_copy.data(), buffer_copy.size(), flags, callback, user_data))
		{
			buf = buffer_copy.data();
			return true;
		}

		return false;
	}

	scoped_id::scoped_id(char const * const str_id)
	{
		ImGui::PushID(str_id);
	}

	scoped_id::scoped_id(int const int_id)
	{
		ImGui::PushID(int_id);
	}

	scoped_id::~scoped_id()
	{
		ImGui::PopID();
	}
}

char const * ion::BoolToString(bool const B)
{
	return B ? "yes" : "no";
}
