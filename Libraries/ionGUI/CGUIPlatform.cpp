
#include "CGUIPlatform.h"


namespace ion
{

	char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data)
	{
		SingletonPointer<CGUIPlatform> ImGUIManager;
		return ImGUIManager->PrimaryWindow->GetClipboardText().c_str();
	}

	void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text)
	{
		SingletonPointer<CGUIPlatform> ImGUIManager;
		ImGUIManager->PrimaryWindow->SetClipboardText(text);
	}

	struct ImGuiViewportData
	{
		CWindow * Window = nullptr;
		bool WindowOwned = false;

		ImGuiViewportData() = default;
		~ImGuiViewportData() { IM_ASSERT(Window == nullptr); }
	};

	void   ImGui_ImplGlfw_CreateWindow(ImGuiViewport       * vp);
	void   ImGui_ImplGlfw_DestroyWindow(ImGuiViewport      * vp);
	void   ImGui_ImplGlfw_ShowWindow(ImGuiViewport         * vp);
	void   ImGui_ImplGlfw_SetWindowPos(ImGuiViewport       * vp, ImVec2 pos);
	ImVec2 ImGui_ImplGlfw_GetWindowPos(ImGuiViewport       * vp);
	void   ImGui_ImplGlfw_SetWindowSize(ImGuiViewport      * vp, ImVec2 size);
	ImVec2 ImGui_ImplGlfw_GetWindowSize(ImGuiViewport      * vp);
	void   ImGui_ImplGlfw_SetWindowFocus(ImGuiViewport     * vp);
	bool   ImGui_ImplGlfw_GetWindowFocus(ImGuiViewport     * vp);
	bool   ImGui_ImplGlfw_GetWindowMinimized(ImGuiViewport * vp);
	void   ImGui_ImplGlfw_SetWindowTitle(ImGuiViewport     * vp, const char * title);
	void   ImGui_ImplGlfw_RenderWindow(ImGuiViewport       * vp, void * render_arg);
	void   ImGui_ImplGlfw_SwapBuffers(ImGuiViewport        * vp, void * render_arg);
	void   ImGui_ImplWin32_SetImeInputPos(ImGuiViewport    * vp, ImVec2 pos);

	bool CGUIPlatform::Init(CWindow * window, char const* const iniFileName)
	{
		PrimaryWindow = window;

		ImGuiIO & io = ImGui::GetIO();
		io.KeyMap[ImGuiKey_Tab]         = (int) EKey::Tab;
		io.KeyMap[ImGuiKey_LeftArrow]   = (int) EKey::Left;
		io.KeyMap[ImGuiKey_RightArrow]  = (int) EKey::Right;
		io.KeyMap[ImGuiKey_UpArrow]     = (int) EKey::Up;
		io.KeyMap[ImGuiKey_DownArrow]   = (int) EKey::Down;
		io.KeyMap[ImGuiKey_Home]        = (int) EKey::Home;
		io.KeyMap[ImGuiKey_End]         = (int) EKey::End;
		io.KeyMap[ImGuiKey_Delete]      = (int) EKey::Delete;
		io.KeyMap[ImGuiKey_Backspace]   = (int) EKey::Backspace;
		io.KeyMap[ImGuiKey_Enter]       = (int) EKey::Enter;
		io.KeyMap[ImGuiKey_KeyPadEnter] = (int) EKey::KeyPadEnter;
		io.KeyMap[ImGuiKey_Escape]      = (int) EKey::Escape;
		io.KeyMap[ImGuiKey_A] = (int) EKey::A;
		io.KeyMap[ImGuiKey_C] = (int) EKey::C;
		io.KeyMap[ImGuiKey_V] = (int) EKey::V;
		io.KeyMap[ImGuiKey_X] = (int) EKey::X;
		io.KeyMap[ImGuiKey_Y] = (int) EKey::Y;
		io.KeyMap[ImGuiKey_Z] = (int) EKey::Z;

		io.SetClipboardTextFn = ImGui_ImplGlfwGL3_SetClipboardText;
		io.GetClipboardTextFn = ImGui_ImplGlfwGL3_GetClipboardText;

		io.IniFilename = iniFileName;


		// Enable Viewports

		io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;

		// Register platform interface (will be coupled with a renderer interface)
		ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
		platform_io.Platform_CreateWindow       = ImGui_ImplGlfw_CreateWindow;
		platform_io.Platform_DestroyWindow      = ImGui_ImplGlfw_DestroyWindow;
		platform_io.Platform_ShowWindow         = ImGui_ImplGlfw_ShowWindow;
		platform_io.Platform_SetWindowPos       = ImGui_ImplGlfw_SetWindowPos;
		platform_io.Platform_GetWindowPos       = ImGui_ImplGlfw_GetWindowPos;
		platform_io.Platform_SetWindowSize      = ImGui_ImplGlfw_SetWindowSize;
		platform_io.Platform_GetWindowSize      = ImGui_ImplGlfw_GetWindowSize;
		platform_io.Platform_SetWindowFocus     = ImGui_ImplGlfw_SetWindowFocus;
		platform_io.Platform_GetWindowFocus     = ImGui_ImplGlfw_GetWindowFocus;
		platform_io.Platform_GetWindowMinimized = ImGui_ImplGlfw_GetWindowMinimized;
		platform_io.Platform_SetWindowTitle     = ImGui_ImplGlfw_SetWindowTitle;
		platform_io.Platform_RenderWindow       = ImGui_ImplGlfw_RenderWindow;
		platform_io.Platform_SwapBuffers        = ImGui_ImplGlfw_SwapBuffers;
		platform_io.Platform_SetImeInputPos     = ImGui_ImplWin32_SetImeInputPos;

		UpdateMonitors();


		ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		ImGuiViewportData * data = new ImGuiViewportData();
		data->Window      = PrimaryWindow;
		data->WindowOwned = false;
		main_viewport->PlatformUserData = data;
		main_viewport->PlatformHandle   = static_cast<void *>(PrimaryWindow);

		return true;
	}

	void CGUIPlatform::Shutdown()
	{
	}

	void CGUIPlatform::NewFrame()
	{
		SingletonPointer<CTimeManager> TimeManager;

		ImGuiIO & io = ImGui::GetIO();

		// Setup display size (every frame to accommodate for window resizing)
		int const w = PrimaryWindow->GetSize().X;
		int const h = PrimaryWindow->GetSize().Y;
		int const display_w = PrimaryWindow->GetFrameBufferSize().X;
		int const display_h = PrimaryWindow->GetFrameBufferSize().Y;
		io.DisplaySize             = vec2f(PrimaryWindow->GetSize());
		if (w > 0 && h > 0)
		{
			io.DisplayFramebufferScale = vec2f((float)display_w / w, (float)display_h / h);
		}

		// Setup time step
		double current_time = TimeManager->GetRunTime();
		io.DeltaTime = Time > 0.0 ? (float) (current_time - Time) : (float) (1.0f / 60.0f);
		Time = current_time;

		UpdateMousePosAndButtons();
		UpdateMouseCursor();

		IsMouseCaptured = io.WantCaptureMouse;
	}

	void CGUIPlatform::OnEvent(IEvent & Event)
	{
		ImGuiIO & io = ImGui::GetIO();

		if (InstanceOf<SKeyboardEvent>(Event))
		{
			SKeyboardEvent KeyboardEvent = As<SKeyboardEvent>(Event);

			if (io.WantCaptureKeyboard)
			{
				Event.Block();
			}

			io.KeysDown[(int) KeyboardEvent.Key] = KeyboardEvent.Pressed;

			io.KeyCtrl  = PrimaryWindow->IsKeyDown(EKey::LeftControl) || PrimaryWindow->IsKeyDown(EKey::RightControl);
			io.KeyShift = PrimaryWindow->IsKeyDown(EKey::LeftShift)   || PrimaryWindow->IsKeyDown(EKey::RightShift);
			io.KeyAlt   = PrimaryWindow->IsKeyDown(EKey::LeftAlt)     || PrimaryWindow->IsKeyDown(EKey::RightAlt);
		}
		else if (InstanceOf<SMouseEvent>(Event))
		{
			SMouseEvent MouseEvent = As<SMouseEvent>(Event);

			if (io.WantCaptureMouse)
			{
				Event.Block();
			}

			switch (MouseEvent.Type)
			{
			case SMouseEvent::EType::Click:
				MouseHeld[(int) MouseEvent.Button] = MouseEvent.Pressed;
				if (MouseEvent.Pressed)
				{
					MouseWasPressed[(int) MouseEvent.Button] = MouseEvent.Pressed;
				}
				break;

			case SMouseEvent::EType::Move:
				break;

			case SMouseEvent::EType::Scroll:
				MouseWheel += MouseEvent.Movement.Y;
				break;
			}
		}
		else if (InstanceOf<SCharacterEvent>(Event))
		{
			SCharacterEvent CharacterEvent = As<SCharacterEvent>(Event);
			io.AddInputCharacter(CharacterEvent.C);
		}
		else if (InstanceOf<SWindowClosedEvent>(Event))
		{
			SWindowClosedEvent WindowEvent = As<SWindowClosedEvent>(Event);

			if (ImGuiViewport * viewport = ImGui::FindViewportByPlatformHandle(WindowEvent.Window))
			{
				viewport->PlatformRequestClose = true;
			}
		}
		else if (InstanceOf<SWindowMovedEvent>(Event))
		{
			SWindowMovedEvent WindowEvent = As<SWindowMovedEvent>(Event);

			if (ImGuiViewport * viewport = ImGui::FindViewportByPlatformHandle(WindowEvent.Window))
			{
				viewport->PlatformRequestMove = true;
			}
		}
		else if (InstanceOf<SWindowResizedEvent>(Event))
		{
			SWindowResizedEvent WindowEvent = As<SWindowResizedEvent>(Event);

			if (ImGuiViewport * viewport = ImGui::FindViewportByPlatformHandle(WindowEvent.Window))
			{
				viewport->PlatformRequestResize = true;
			}
		}
	}

	void CGUIPlatform::UpdateMousePosAndButtons()
	{
		SingletonPointer<CWindowManager> windowManager;

		ImGuiIO & io = ImGui::GetIO();

		if (io.WantSetMousePos)
		{
			Log::Info("imgui attempting to set mouse position.");
		}

		// Update buttons
		for (int i = 0; i < 3; i++)
		{
			// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
			io.MouseDown[i] = MouseWasPressed[i] || MouseHeld[i];
			MouseWasPressed[i] = false;
		}

		vector<ion::CWindow *> windows;
		windows.push_back(windowManager->GetPrimaryWindow());

		AddAtEnd(windows, ViewportWindows);

		// Update mouse position
		// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
		for (auto window : windows)
		{
			if (window->IsFocused())
			{
				// Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
				io.MousePos = window->GetCursorLocation() + vec2f(window->GetPosition());
			}
		}

		io.MouseWheel = MouseWheel;
		MouseWheel = 0;
	}

	void CGUIPlatform::UpdateMouseCursor()
	{
	}

	void CGUIPlatform::UpdateMonitors()
	{
		SingletonPointer<CWindowManager> windowManager;

		ImGuiPlatformIO & platformIO = ImGui::GetPlatformIO();

		platformIO.Monitors.clear();
		for (SMonitorInfo const & info : windowManager->GetMonitors())
		{
			ImGuiPlatformMonitor monitor;
			monitor.MainPos  = vec2f(info.Position);
			monitor.MainSize = vec2f(info.Size);
			monitor.WorkPos  = vec2f(info.WorkPosition);
			monitor.WorkSize = vec2f(info.WorkSize);
			platformIO.Monitors.push_back(monitor);
		}
	}

	CGUIPlatform::CGUIPlatform()
	{
		for (int i = 0; i < 3; ++ i)
		{
			MouseWasPressed[i] = false;
			MouseHeld[i] = false;
		}
	}



	///////////////
	// Viewports //
	///////////////

	void ImGui_ImplGlfw_CreateWindow(ImGuiViewport * viewport)
	{
		SingletonPointer<CGUIPlatform> platformManager;
		SingletonPointer<CWindowManager> windowManager;

		ImGuiViewportData* data = new ImGuiViewportData();
		viewport->PlatformUserData = data;

		data->Window = windowManager->CreateGUIWindow(
			vec2i(vec2f(viewport->Pos)),
			vec2i(vec2f(viewport->Size)),
			(viewport->Flags & ImGuiViewportFlags_NoDecoration));
		data->WindowOwned = true;
		viewport->PlatformHandle = (void *) data->Window;

		data->Window->AddListener(platformManager.Get());
		platformManager->ViewportWindows.push_back(data->Window);
	}

	void ImGui_ImplGlfw_DestroyWindow(ImGuiViewport * viewport)
	{
		SingletonPointer<CGUIPlatform> platformManager;
		SingletonPointer<CWindowManager> windowManager;

		if (ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData)
		{
			EraseRemove(platformManager->ViewportWindows, data->Window);

			if (data->WindowOwned)
			{
				windowManager->CloseWindow(data->Window);
			}
			data->Window = nullptr;
			delete data;
		}

		viewport->PlatformUserData = viewport->PlatformHandle = nullptr;
	}

	void ImGui_ImplGlfw_ShowWindow(ImGuiViewport * viewport)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		data->Window->Show();
	}

	void ImGui_ImplGlfw_SetWindowPos(ImGuiViewport * viewport, ImVec2 pos)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return data->Window->SetPosition(vec2i(vec2f(pos)));
	}

	ImVec2 ImGui_ImplGlfw_GetWindowPos(ImGuiViewport * viewport)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return vec2f(data->Window->GetPosition());
	}

	void ImGui_ImplGlfw_SetWindowSize(ImGuiViewport * viewport, ImVec2 size)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return data->Window->SetSize(vec2i(vec2f(size)));
	}

	ImVec2 ImGui_ImplGlfw_GetWindowSize(ImGuiViewport * viewport)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return vec2f(data->Window->GetSize());
	}

	void ImGui_ImplGlfw_SetWindowFocus(ImGuiViewport * viewport)
	{
		// Do nothing?
		Log::Info("GLFW attempting to set window focus.");
	}

	bool ImGui_ImplGlfw_GetWindowFocus(ImGuiViewport * viewport)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return data->Window->IsFocused();
	}

	bool ImGui_ImplGlfw_GetWindowMinimized(ImGuiViewport * viewport)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return data->Window->IsMinimized();
	}

	void ImGui_ImplGlfw_SetWindowTitle(ImGuiViewport * viewport, const char* title)
	{
		ImGuiViewportData * data = (ImGuiViewportData *) viewport->PlatformUserData;
		return data->Window->SetTitle(title);
	}

	void ImGui_ImplGlfw_RenderWindow(ImGuiViewport * viewport, void* render_arg)
	{
		// Do nothing
	}

	void ImGui_ImplGlfw_SwapBuffers(ImGuiViewport * viewport, void* render_arg)
	{
		// Do nothing
	}

	void ImGui_ImplWin32_SetImeInputPos(ImGuiViewport * viewport, ImVec2 pos)
	{
		// TODO ??
	}

}
