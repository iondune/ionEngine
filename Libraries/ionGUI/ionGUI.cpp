
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

	bool ColorEdit3(const char * label, color3i & Color)
	{
		color3f c = Color;
		if (ColorEdit3(label, c))
		{
			Color = c;
			return true;
		}
		return false;
	}

	bool ColorEdit4(const char * label, color4f & Color)
	{
		float c[4] = { Color.Red, Color.Green, Color.Blue, Color.Alpha };
		if (ImGui::ColorEdit4(label, c))
		{
			Color = color4f(c[0], c[1], c[2], c[3]);
			return true;
		}
		return false;
	}

	bool ColorEdit4(const char * label, color4i & Color)
	{
		color4f c = Color;
		if (ColorEdit4(label, c))
		{
			Color = c;
			return true;
		}
		return false;
	}

	bool ColorPicker3(const char* label, ion::color3f & Color)
	{
		float c[3] = { Color.Red, Color.Green, Color.Blue };
		if (ImGui::ColorPicker3(label, c))
		{
			Color = color3f(c[0], c[1], c[2]);
			return true;
		}
		return false;
	}

	bool ColorPicker3(const char* label, ion::color3i & Color)
	{
		color3f c = Color;
		if (ColorPicker3(label, c))
		{
			Color = c;
			return true;
		}
		return false;
	}

	bool ColorPicker4(const char* label, ion::color4f & Color)
	{
		float c[4] = { Color.Red, Color.Green, Color.Blue, Color.Alpha };
		if (ImGui::ColorPicker4(label, c))
		{
			Color = color4f(c[0], c[1], c[2], c[3]);
			return true;
		}
		return false;
	}

	bool ColorPicker4(const char* label, ion::color4i & Color)
	{
		color4f c = Color;
		if (ColorPicker4(label, c))
		{
			Color = c;
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

	bool DragVec3(const char * label, ion::vec3i & v, float v_speed, int v_min, int v_max, const char* display_format)
	{
		int vals[3] = { v.X, v.Y, v.Z };
		if (ImGui::DragInt3(label, vals, v_speed, v_min, v_max, display_format))
		{
			v = vec3i(vals[0], vals[1], vals[2]);
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

	bool SliderVec2(const char * label, ion::vec2i & v, int v_min, int v_max, const char * display_format)
	{
		int vals[2] = { v.X, v.Y };
		if (ImGui::SliderInt2(label, vals, v_min, v_max, display_format))
		{
			v = vec2i(vals[0], vals[1]);
			return true;
		}
		return false;
	}

	bool SliderVec2(const char * label, ion::vec2f & v, float v_min, float v_max, const char * display_format, float power)
	{
		float vals[2] = { v.X, v.Y };
		if (ImGui::SliderFloat2(label, vals, v_min, v_max, display_format, power))
		{
			v = vec2f(vals[0], vals[1]);
			return true;
		}
		return false;
	}

	bool SliderVec3(const char * label, ion::vec3i & v, int v_min, int v_max, const char * display_format)
	{
		int vals[3] = { v.X, v.Y, v.Z };
		if (ImGui::SliderInt3(label, vals, v_min, v_max, display_format))
		{
			v = vec3i(vals[0], vals[1], vals[2]);
			return true;
		}
		return false;
	}

	bool SliderVec3(const char * label, ion::vec3f & v, float v_min, float v_max, const char * display_format, float power)
	{
		float vals[3] = { v.X, v.Y, v.Z };
		if (ImGui::SliderFloat3(label, vals, v_min, v_max, display_format, power))
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

	void TextBool(const char* label, const bool value)
	{
		static constexpr float high = 1.f;
		static constexpr float low = 0.6f;

		ImGui::TextUnformatted(label);
		ImGui::SameLine();
		if (value)
		{
			ImGui::TextColored(ImVec4(low,high,low,1.0f), "true");
		}
		else
		{
			ImGui::TextColored(ImVec4(high,low,low,1.0f), "false");
		}
	}

	bool HueButton(const char* label, const float hue)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
		bool const pressed = ImGui::Button(label);
		ImGui::PopStyleColor(3);
		return pressed;
	}

	void Image(SharedPointer<Graphics::ITexture2D> texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col)
	{
		ImGui::Image(CGUIManager::TextureID(texture), size, uv0, uv1, tint_col, border_col);
	}

	bool ImageButton(SharedPointer<Graphics::ITexture2D> texture, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
	{
		return ImGui::ImageButton(CGUIManager::TextureID(texture), size, uv0, uv1, frame_padding, bg_col, tint_col);
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
