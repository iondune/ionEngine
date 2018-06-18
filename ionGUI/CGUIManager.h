
#pragma once

#include <ionCore.h>
#include <ionWindow.h>
#include <ionGraphics.h>

#include "imGUI.h"


namespace ion
{
	namespace Graphics
	{
		class CD3D11Implementation;
	}

	class CGUIManager : public Singleton<CGUIManager>, public IEventListener
	{

	public:

		bool Init(CWindow * Window, Graphics::CD3D11Implementation * GraphicsImplementation, float const DefaultFontSize = 18.f);
		void Shutdown();
		void NewFrame();
		void RenderDrawData(ImDrawData* draw_data);

		void Draw();

		template <typename... Args>
		void Text(vec2i const & Position, color3i const & Color, char const * const Format, Args const &... args)
		{
			TextUnformatted(Position, Color, tfm::format(Format, args...));
		}

		void TextUnformatted(vec2i const & Position, color3i const & Color, string const & Text);

		void OnEvent(IEvent & Event);

	protected:

		void AddFontFromFile(string const & FileName, float const Size);
		ImTextureID GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture);

		void CreateFontsTexture();
		bool CreateDeviceObjects();
		void InvalidateDeviceObjects();

		size_t const StartVboMaxSize = 20000;

		CWindow * Window = nullptr;
		double Time = 0;
		bool MouseWasPressed[3];
		bool MouseHeld[3];
		float MouseWheel = 0;
		uint FontTexture = 0;
		int ShaderHandle = 0, VertHandle = 0, FragHandle = 0;
		int AttribLocationTex = 0, AttribLocationProjMtx = 0;
		int AttribLocationPosition = 0, AttribLocationUV = 0, AttribLocationColor = 0;
		uint VboHandle = 0, VaoHandle = 0, ElementsHandle = 0;

		struct SDrawText
		{
			vec2i Position;
			color3i Color;
			string Text;
		};

		vector<SDrawText> TextQueue;

	private:

		friend class Singleton<CGUIManager>;

		CGUIManager();

		friend char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data);
		friend void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text);

	};

}
