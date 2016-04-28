
#pragma once

#include <ionMath.h>
#include <ionFramework.h>
#include <ionWindow.h>
#include <imgui.h>


namespace ion
{

	class CGUIManager : public Singleton<CGUIManager>, public IEventListener
	{

	public:

		bool Init(CWindow * Window);
		void Shutdown();
		void NewFrame();
	void Draw();

	template <typename... Args>
	void Text(vec2i const & Position, char const * const Format, Args const &... args)
	{
		TextUnformatted(Position, tfm::format(Format, args...));
	}

	void TextUnformatted(vec2i const & Position, string const & Text);

		void OnEvent(IEvent & Event);
		void AddFontFromFile(string const & FileName, float const Size);

		ImGuiIO & IO = ImGui::GetIO();

	protected:

		void DrawCallback(ImDrawData* draw_data);
		void CreateFontsTexture();
		bool CreateDeviceObjects();

		size_t const StartVboMaxSize = 20000;

		CWindow * Window = nullptr;
		double Time = 0;
		bool MousePressed[3];
		float MouseWheel = 0;
		uint FontTexture = 0;
		int ShaderHandle = 0, VertHandle = 0, FragHandle = 0;
		int AttribLocationTex = 0, AttribLocationProjMtx = 0;
		int AttribLocationPosition = 0, AttribLocationUV = 0, AttribLocationColor = 0;
		uint VboHandle = 0, VaoHandle = 0, ElementsHandle = 0;

	struct SDrawText
	{
		vec2i Position;
		string Text;
	};

	vector<SDrawText> TextQueue;

	private:

		friend class Singleton<CGUIManager>;

		CGUIManager();

		friend void ImGui_ImplGlfwGL3_RenderDrawLists(ImDrawData* draw_data);
		friend char const * ImGui_ImplGlfwGL3_GetClipboardText();
		friend void ImGui_ImplGlfwGL3_SetClipboardText(const char* text);

	};

}
