
#pragma once

#include <ionMath.h>
#include "imGUI.h"
#include "CGUIManager.h"
#include "CWindowWidget.h"


namespace ImGui
{
	bool SliderDouble(const char* label, double* v, double v_min, double v_max, const char* display_format = "%.3f", double power = 1.0);

	bool ColorEdit3(const char* label, ion::color3f & Color);
	bool ColorEdit3(const char* label, ion::color3i & Color);
	bool ColorEdit4(const char* label, ion::color4f & Color);
	bool ColorEdit4(const char* label, ion::color4i & Color);

	bool ColorPicker3(const char* label, ion::color3f & Color);
	bool ColorPicker3(const char* label, ion::color3i & Color);
	bool ColorPicker4(const char* label, ion::color4f & Color);
	bool ColorPicker4(const char* label, ion::color4i & Color);

	bool DragVec2(const char * label, ion::vec2i & v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool DragVec2(const char * label, ion::vec2f & v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
	bool DragVec3(const char * label, ion::vec3i & v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
	bool DragVec3(const char * label, ion::vec3f & v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);

	bool SliderVec2(const char* label, ion::vec2i & v, int v_min, int v_max, const char* display_format = "%.3f");
	bool SliderVec2(const char* label, ion::vec2f & v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
	bool SliderVec3(const char* label, ion::vec3i & v, int v_min, int v_max, const char* display_format = "%.3f");
	bool SliderVec3(const char* label, ion::vec3f & v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);

	bool Combo(const char* label, int* current_item, std::initializer_list<char const *> const & items, int height_in_items = -1);
	bool Combo(const char* label, int* current_item, std::vector<ion::string> const & items, int height_in_items = -1);

	bool InputText(const char* label, ion::string & buf, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = nullptr, void* user_data = nullptr);

	void TextBool(const char* label, const bool value);

	bool HueButton(const char* label, const float hue);

	void Image(ion::SharedPointer<ion::Graphics::ITexture2D> texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_col = ImVec4(1,1,1,1), const ImVec4& border_col = ImVec4(0,0,0,0));
	bool ImageButton(ion::SharedPointer<ion::Graphics::ITexture2D> texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,0), const ImVec4& tint_col = ImVec4(1,1,1,1));    // <0 frame_padding uses default frame padding settings. 0 for no padding

	template <typename... Args>
	static void PushIDString(char const * const Format, Args const &... args)
	{
		ion::string Buffer;
		Buffer = ion::String::Build(Format, args...);
		ImGui::PushID(Buffer.c_str(), Buffer.c_str() + Buffer.length());
	}

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
