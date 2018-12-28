
#include "CGUIManager.h"
#include <ionGraphicsD3D11/CD3D11Implementation.h>
#include <ionGraphicsD3D11/CTexture.h>


namespace ion
{

	void CGUIManager::OnEvent(IEvent & Event)
	{
		ImGuiIO& io = ImGui::GetIO();

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
			if (CharacterEvent.C > 0)
				io.AddInputCharacter(CharacterEvent.C);
		}
	}

	char const * ImGui_ImplGlfwGL3_GetClipboardText(void * user_data)
	{
		SingletonPointer<CGUIManager> ImGUIManager;
		return ImGUIManager->Window->GetClipboardText().c_str();
	}

	void ImGui_ImplGlfwGL3_SetClipboardText(void * user_data, char const * text)
	{
		SingletonPointer<CGUIManager> ImGUIManager;
		ImGUIManager->Window->SetClipboardText(text);
	}

	void CGUIManager::NewFrame()
	{
		SingletonPointer<CTimeManager> TimeManager;

		if (! FontTexture)
			CreateDeviceObjects();

		ImGuiIO& io = ImGui::GetIO();

		// Setup display size (every frame to accommodate for window resizing)
		int w = Window->GetSize().X, h = Window->GetSize().Y;
		int display_w = Window->GetFrameBufferSize().X, display_h = Window->GetFrameBufferSize().Y;
		io.DisplaySize = ImVec2((float) w, (float) h);
		io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float) display_w / w) : 0, h > 0 ? ((float) display_h / h) : 0);

		// Setup time step
		double current_time = TimeManager->GetRunTime();
		io.DeltaTime = Time > 0.0 ? (float) (current_time - Time) : (float) (1.0f / 60.0f);
		Time = current_time;

		// Setup inputs
		// (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
		if (Window->IsFocused())
		{
			double mouse_x, mouse_y;
			mouse_x = Window->GetCursorLocation().X;
			mouse_y = Window->GetCursorLocation().Y;
			io.MousePos = ImVec2((float) mouse_x, (float) mouse_y);   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
		}
		else
		{
			io.MousePos = ImVec2(-1, -1);
		}

		for (int i = 0; i < 3; i++)
		{
			io.MouseDown[i] = MouseWasPressed[i] || MouseHeld[i];    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
			MouseWasPressed[i] = false;
		}

		io.MouseWheel = MouseWheel;
		MouseWheel = 0;

		// Start the frame
		ImGui::NewFrame();
	}


}
