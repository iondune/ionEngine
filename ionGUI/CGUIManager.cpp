
#include "CGUIManager.h"
#include <ionGraphicsGL/CTexture.h>


namespace ion
{

	void CGUIManager::AddFontFromFile(string const & FileName, float const Size)
	{
		ImGuiIO & io = ImGui::GetIO();
		ImFont * my_font = io.Fonts->AddFontFromFileTTF(FileName.c_str(), Size);
	}

	ImTextureID CGUIManager::GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture)
	{
		SharedPointer<Graphics::GL::CTexture const> TextureImplementation = std::dynamic_pointer_cast<Graphics::GL::CTexture const>(Texture);
		return  (void *) (intptr_t) TextureImplementation->Handle;
	}

	bool CGUIManager::Init(CWindow * window, float const DefaultFontSize)
	{
		bool Success = true;
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		Success &= PlatformImplementation->Init(window);
		Success &= RendererImplementation->Init(window);

		AddListener(PlatformImplementation.Get());
		AddListener(RendererImplementation.Get());

		ImGuiIO & io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF((string(ION_PROJECT_BASE_DIRECTORY) + "Fonts/Roboto-Regular.ttf").c_str(), DefaultFontSize);

		return Success;
	}

	void CGUIManager::Shutdown()
	{
		PlatformImplementation->Shutdown();
		RendererImplementation->Shutdown();

		ImGui::DestroyContext();
	}

	void CGUIManager::NewFrame()
	{
		PlatformImplementation->NewFrame();
		RendererImplementation->NewFrame();

		// Start the frame
		ImGui::NewFrame();
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
		RendererImplementation->Draw(ImGui::GetDrawData());
	}

	void CGUIManager::TextUnformatted(vec2i const & Position, color3i const & Color, string const & Text)
	{
		SDrawText Draw;
		Draw.Text = Text;
		Draw.Position = Position;
		Draw.Color = Color;

		TextQueue.push_back(Draw);
	}

}
