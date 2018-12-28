
#include "CGUIPlatform.h"


namespace ion
{

	char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data)
	{
		SingletonPointer<CGUIPlatform> ImGUIManager;
		return ImGUIManager->Window->GetClipboardText().c_str();
	}

	void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text)
	{
		SingletonPointer<CGUIPlatform> ImGUIManager;
		ImGUIManager->Window->SetClipboardText(text);
	}

	bool CGUIPlatform::Init(CWindow * window)
	{
		Window = window;

		ImGuiIO & io = ImGui::GetIO();
		io.KeyMap[ImGuiKey_Tab]        = (int) EKey::Tab;
		io.KeyMap[ImGuiKey_LeftArrow]  = (int) EKey::Left;
		io.KeyMap[ImGuiKey_RightArrow] = (int) EKey::Right;
		io.KeyMap[ImGuiKey_UpArrow]    = (int) EKey::Up;
		io.KeyMap[ImGuiKey_DownArrow]  = (int) EKey::Down;
		io.KeyMap[ImGuiKey_Home]       = (int) EKey::Home;
		io.KeyMap[ImGuiKey_End]        = (int) EKey::End;
		io.KeyMap[ImGuiKey_Delete]     = (int) EKey::Delete;
		io.KeyMap[ImGuiKey_Backspace]  = (int) EKey::Backspace;
		io.KeyMap[ImGuiKey_Enter]      = (int) EKey::Enter;
		io.KeyMap[ImGuiKey_Escape]     = (int) EKey::Escape;
		io.KeyMap[ImGuiKey_A] = (int) EKey::A;
		io.KeyMap[ImGuiKey_C] = (int) EKey::C;
		io.KeyMap[ImGuiKey_V] = (int) EKey::V;
		io.KeyMap[ImGuiKey_X] = (int) EKey::X;
		io.KeyMap[ImGuiKey_Y] = (int) EKey::Y;
		io.KeyMap[ImGuiKey_Z] = (int) EKey::Z;

		io.SetClipboardTextFn = ImGui_ImplGlfwGL3_SetClipboardText;
		io.GetClipboardTextFn = ImGui_ImplGlfwGL3_GetClipboardText;

		io.IniFilename = nullptr;

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
		int const w = Window->GetSize().X;
		int const h = Window->GetSize().Y;
		int const display_w = Window->GetFrameBufferSize().X;
		int const display_h = Window->GetFrameBufferSize().Y;
		io.DisplaySize = vec2f(Window->GetSize());
		io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float) display_w / w) : 0, h > 0 ? ((float) display_h / h) : 0);

		// Setup time step
		double current_time = TimeManager->GetRunTime();
		io.DeltaTime = Time > 0.0 ? (float) (current_time - Time) : (float) (1.0f / 60.0f);
		Time = current_time;

		UpdateMousePosAndButtons();
		UpdateMouseCursor();
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

			// Hack/workaround to make KP enter work like enter
			// Will cause problems if regular Enter and KP Enter are pressed simultaneously
			// Don't do that
			if (KeyboardEvent.Key == EKey::KeyPadEnter)
			{
				io.KeysDown[(int) EKey::Enter] = KeyboardEvent.Pressed;
			}

			io.KeyCtrl = Window->IsKeyDown(EKey::LeftControl) || Window->IsKeyDown(EKey::RightControl);
			io.KeyShift = Window->IsKeyDown(EKey::LeftShift) || Window->IsKeyDown(EKey::RightShift);
			io.KeyAlt = Window->IsKeyDown(EKey::LeftAlt) || Window->IsKeyDown(EKey::RightAlt);
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

			if (CharacterEvent.C > 0 && CharacterEvent.C < 0x10000)
				io.AddInputCharacter(CharacterEvent.C);
		}
	}

	void CGUIPlatform::UpdateMousePosAndButtons()
	{
		ImGuiIO & io = ImGui::GetIO();

		// Update buttons
		for (int i = 0; i < 3; i++)
		{
			// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
			io.MouseDown[i] = MouseWasPressed[i] || MouseHeld[i];
			MouseWasPressed[i] = false;
		}

		// Update mouse position
		// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
		if (Window->IsFocused())
		{
			// Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
			io.MousePos = Window->GetCursorLocation();
		}
		else
		{
			io.MousePos = ImVec2(-1, -1);
		}

		io.MouseWheel = MouseWheel;
		MouseWheel = 0;
	}

	void CGUIPlatform::UpdateMouseCursor()
	{
	}

	CGUIPlatform::CGUIPlatform()
	{
		for (int i = 0; i < 3; ++ i)
		{
			MouseWasPressed[i] = false;
			MouseHeld[i] = false;
		}
	}

}
