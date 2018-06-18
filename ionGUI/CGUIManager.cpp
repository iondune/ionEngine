
#include "CGUIManager.h"
#include <ionGraphicsD3D11/CD3D11Implementation.h>
#include <ionGraphicsD3D11/CTexture.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


// Window data
extern HWND                     g_hWnd;
extern ID3D11Device*            g_pd3dDevice;
extern ID3D11DeviceContext*     g_pd3dDeviceContext;


namespace ion
{

	void CGUIManager::AddFontFromFile(string const & FileName, float const Size)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* my_font = io.Fonts->AddFontFromFileTTF(FileName.c_str(), Size);
	}

	ImTextureID CGUIManager::GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture)
	{
		SharedPointer<Graphics::D3D11::CTexture2D const> TextureImplementation = std::dynamic_pointer_cast<Graphics::D3D11::CTexture2D const>(Texture);
		return  (void *) TextureImplementation->Texture2D;
	}

	bool CGUIManager::Init(CWindow * Window, Graphics::CD3D11Implementation * GraphicsImplementation, float const DefaultFontSize)
	{
		this->Window = Window;

		g_hWnd = glfwGetWin32Window(Window->GetHandle());;
		g_pd3dDevice = GraphicsImplementation->GetDevice();
		g_pd3dDeviceContext = GraphicsImplementation->GetImmediateContext();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		// Setup back-end capabilities flags
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;   // We can honor GetMouseCursor() values (optional)
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;    // We can honor io.WantSetMousePos requests (optional, rarely used)

		io.KeyMap[ImGuiKey_Tab] = (int) EKey::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = (int) EKey::Left;
		io.KeyMap[ImGuiKey_RightArrow] = (int) EKey::Right;
		io.KeyMap[ImGuiKey_UpArrow] = (int) EKey::Up;
		io.KeyMap[ImGuiKey_DownArrow] = (int) EKey::Down;
		io.KeyMap[ImGuiKey_Home] = (int) EKey::Home;
		io.KeyMap[ImGuiKey_End] = (int) EKey::End;
		io.KeyMap[ImGuiKey_Delete] = (int) EKey::Delete;
		io.KeyMap[ImGuiKey_Backspace] = (int) EKey::Backspace;
		io.KeyMap[ImGuiKey_Enter] = (int) EKey::Enter;
		io.KeyMap[ImGuiKey_Escape] = (int) EKey::Escape;
		io.KeyMap[ImGuiKey_A] = (int) EKey::A;
		io.KeyMap[ImGuiKey_C] = (int) EKey::C;
		io.KeyMap[ImGuiKey_V] = (int) EKey::V;
		io.KeyMap[ImGuiKey_X] = (int) EKey::X;
		io.KeyMap[ImGuiKey_Y] = (int) EKey::Y;
		io.KeyMap[ImGuiKey_Z] = (int) EKey::Z;

		io.SetClipboardTextFn = ImGui_ImplGlfwGL3_SetClipboardText;
		io.GetClipboardTextFn = ImGui_ImplGlfwGL3_GetClipboardText;

		io.ImeWindowHandle = g_hWnd;
		io.IniFilename = nullptr;

		io.Fonts->AddFontFromFileTTF((string(ION_PROJECT_BASE_DIRECTORY) + "Fonts/Roboto-Regular.ttf").c_str(), DefaultFontSize);

		ImGui::StyleColorsDark();

		return true;
	}

	void CGUIManager::Draw()
	{
		ImGui::SetNextWindowPos(ImVec2(-1000, -1000));
		ImGui::SetNextWindowSize(ImVec2(100000, 100000));
		if (ImGui::Begin("GlobalScreen", nullptr, ImVec2(0, 0), 0.0f,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs))
		{
			ImDrawList * DrawList = ImGui::GetWindowDrawList();

			for (auto Text : TextQueue)
			{
				uint Red = Text.Color.Red;
				uint Green = Text.Color.Green;
				uint Blue = Text.Color.Blue;
				DrawList->AddText(ImVec2((float) Text.Position.X, (float) Text.Position.Y), (0xFF000000) | (Blue << 16) | (Green << 8) | (Red), Text.Text.c_str());
			}
			TextQueue.clear();

			ImGui::End();
		}
		ImGui::Render();
		RenderDrawData(ImGui::GetDrawData());
	}

	void CGUIManager::TextUnformatted(vec2i const & Position, color3i const & Color, string const & Text)
	{
		SDrawText Draw;
		Draw.Text = Text;
		Draw.Position = Position;
		Draw.Color = Color;

		TextQueue.push_back(Draw);
	}

	CGUIManager::CGUIManager()
	{
		for (int i = 0; i < 3; ++ i)
		{
			MouseWasPressed[i] = false;
			MouseHeld[i] = false;
		}
	}

}
