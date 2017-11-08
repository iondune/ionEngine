
#pragma once

#include <ionMath.h>
#include "imGUI.h"
#include "CGUIManager.h"
#include "CWindowWidget.h"


namespace ImGui
{
	bool SliderDouble(const char* label, double* v, double v_min, double v_max, const char* display_format = "%.3f", double power = 1.0);
	bool ColorEdit3(const char* label, ion::color3f & Color);

	bool ColorPicker4(float* col, bool show_alpha);
	bool ColorPicker3(float col[3]);
	bool ColorPicker3(ion::color3f & col);
	bool ColorPicker3(ion::color3i & col);

	bool DragVec2(const char * label, ion::vec2i & v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool DragVec2(const char * label, ion::vec2f & v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool DragVec3(const char * label, ion::vec3f & v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);

	bool Combo(const char* label, int* current_item, std::initializer_list<char const *> const & items, int height_in_items = -1);
	bool Combo(const char* label, int* current_item, std::vector<ion::string> const & items, int height_in_items = -1);

	bool InputText(const char* label, ion::string & buf, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = nullptr, void* user_data = nullptr);

	class scoped_id
	{

	private:

		scoped_id(scoped_id const &) = delete;
		scoped_id(scoped_id const &&) = delete;
		scoped_id & operator =(scoped_id const &) = delete;
		scoped_id & operator =(scoped_id const &&) = delete;

	public:

		scoped_id(char const * const str_id);
		scoped_id(int const int_id);
		~scoped_id();
	};
}

namespace ion
{

	char const * BoolToString(bool const B);

}
