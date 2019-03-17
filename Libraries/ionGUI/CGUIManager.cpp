
#include "CGUIManager.h"
#include <ionGraphicsD3D11/CTexture.h>
#include <ionGraphicsD3D11/CRenderTarget.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


namespace ion
{

	void CGUIManager::AddFontFromFile(string const & FileName, float const Size)
	{
		ImGuiIO & io = ImGui::GetIO();
		ImFont * my_font = io.Fonts->AddFontFromFileTTF(FileName.c_str(), Size);
	}

	ImTextureID CGUIManager::GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture)
	{
		SharedPointer<Graphics::D3D11::CTexture2D const> TextureImplementation = std::dynamic_pointer_cast<Graphics::D3D11::CTexture2D const>(Texture);
		return  (void *) TextureImplementation->ShaderResourceView;
	}

	bool CGUIManager::Init(CWindow * window, IGraphicsImplementation * GraphicsImplementation, float const DefaultFontSize)
	{
		bool Success = true;
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO & io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		Success &= PlatformImplementation->Init(window);
		Success &= RendererImplementation->Init(window, GraphicsImplementation);

		AddListener(PlatformImplementation.Get());
		AddListener(RendererImplementation.Get());

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

		ImGui::NewFrame();
	}

	void CGUIManager::Draw()
	{
		ImDrawList * DrawList = ImGui::GetBackgroundDrawList();

		for (auto Text : TextQueue)
		{
			uint  const Red        = Text.Color.Red;
			uint  const Green      = Text.Color.Green;
			uint  const Blue       = Text.Color.Blue;
			vec2f const Position   = Text.Position + PlatformImplementation->PrimaryWindow->GetPosition();
			DrawList->AddText(Position, (0xFF000000) | (Blue << 16) | (Green << 8) | (Red), Text.Text.c_str());
		}
		TextQueue.clear();

		ImGui::Render();
		RendererImplementation->Draw(ImGui::GetDrawData());

		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();

		// CurrentlyBound render target no longer correct after imgui render code with multiple viewports
		Graphics::D3D11::CRenderTarget::InvalidateCurrentlyBound();
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
