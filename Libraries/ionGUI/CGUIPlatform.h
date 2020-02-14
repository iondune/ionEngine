
#pragma once

#include <ionCore.h>
#include <ionWindow.h>
#include <ionGraphics.h>

#include "imGUI.h"


namespace ion
{

	class CGUIPlatform : public Singleton<CGUIPlatform>, public IEventListener
	{

	public:

		bool Init(CWindow * Window, char const * const iniFileName = nullptr);
		void Shutdown();
		void NewFrame();

		void OnEvent(IEvent & Event);

		CWindow * PrimaryWindow = nullptr;
		bool IsMouseCaptured = false;

	protected:

		void UpdateMousePosAndButtons();
		void UpdateMouseCursor();
		void UpdateMonitors();

		double Time = 0;
		bool MouseWasPressed[3];
		bool MouseHeld[3];
		float MouseWheel = 0;

		vector<ion::CWindow *> ViewportWindows;

	private:

		friend class Singleton<CGUIPlatform>;
		CGUIPlatform();

		friend char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data);
		friend void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text);

		friend void ImGui_ImplGlfw_CreateWindow(ImGuiViewport * viewport);
		friend void ImGui_ImplGlfw_DestroyWindow(ImGuiViewport * viewport);

	};

}
