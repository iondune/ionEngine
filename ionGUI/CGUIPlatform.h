
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

		bool Init(CWindow * Window);
		void Shutdown();
		void NewFrame();

		void OnEvent(IEvent & Event);

	protected:

		void UpdateMousePosAndButtons();
		void UpdateMouseCursor();

		CWindow * Window = nullptr;
		double Time = 0;
		bool MouseWasPressed[3];
		bool MouseHeld[3];
		float MouseWheel = 0;

	private:

		friend class Singleton<CGUIPlatform>;
		CGUIPlatform();

		friend void ImGui_ImplGlfwGL3_RenderDrawLists(ImDrawData* draw_data);
		friend char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data);
		friend void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text);

	};

}
