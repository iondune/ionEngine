
#include "CGUIManager.h"
#include <ionGraphicsD3D11/CTexture.h>
#include <ionGraphicsD3D11/CRenderTarget.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "imgui_impl_dx11.h"


namespace ion
{

	void CGUIManager::AddFontFromFile(string const & FileName, float const Size)
	{
		ImGuiIO & io = ImGui::GetIO();
		ImFont * my_font = io.Fonts->AddFontFromFileTTF(FileName.c_str(), Size);
	}

	ImTextureID CGUIManager::GetTextureID(SharedPointer<Graphics::ITexture2D> const Texture)
	{
		static std::unordered_map<Graphics::ITexture2D *, GuiTextureState *> textureCache;

		GuiTextureState * state = nullptr;

		auto it = textureCache.find(Texture.get());

		if (it == textureCache.end())
		{
			SharedPointer<Graphics::D3D11::CTexture2D const> TextureImplementation = std::dynamic_pointer_cast<Graphics::D3D11::CTexture2D const>(Texture);

			state = new GuiTextureState();
			state->ShaderResourceView = TextureImplementation->ShaderResourceView;
			state->SamplerState = TextureImplementation->SamplerState;
			textureCache[Texture.get()] = state;
		}
		else
		{
			state = it->second;
		}

		return state;
	}

	ImTextureID CGUIManager::TextureID(SharedPointer<Graphics::ITexture2D> const Texture)
	{
		return CGUIManager::Get().GetTextureID(Texture);
	}

	bool CGUIManager::Init(CWindow * window, IGraphicsImplementation * GraphicsImplementation, float const DefaultFontSize, char const* const iniFileName, char const * const fontFilename)
	{
		bool Success = true;
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO & io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		Success &= PlatformImplementation->Init(window, iniFileName);
		Success &= RendererImplementation->Init(window, GraphicsImplementation);

		AddListener(PlatformImplementation.Get());
		AddListener(RendererImplementation.Get());
		PlatformImplementation->AddListener(EventRoot = new IEventListener());

		if (fontFilename)
		{
			io.Fonts->AddFontFromFileTTF(fontFilename, DefaultFontSize);
		}
		else
		{
			io.Fonts->AddFontFromFileTTF((string(ION_PROJECT_BASE_DIRECTORY) + "Fonts/Roboto-Regular.ttf").c_str(), DefaultFontSize);
		}

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
			vec2f const Position   = vec2f(Text.Position + PlatformImplementation->PrimaryWindow->GetPosition());
			DrawList->AddText(Position, (0xFF000000) | (Blue << 16) | (Green << 8) | (Red), Text.Text.c_str());
		}
		TextQueue.clear();

		for (auto Image : ImageQueue)
		{
			DrawList->AddImage(GetTextureID(Image.Texture),
				vec2f(Image.Position + PlatformImplementation->PrimaryWindow->GetPosition()),
				vec2f(Image.Position + Image.Size + PlatformImplementation->PrimaryWindow->GetPosition()),
				vec2f(0, 1),
				vec2f(1, 0)
			);
		}
		ImageQueue.clear();

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

	void CGUIManager::Image(SharedPointer<Graphics::ITexture2D> const Texture, vec2i const Position, vec2i const Size)
	{
		SDrawImage Draw;
		Draw.Texture = Texture;
		Draw.Position = Position;
		Draw.Size = Size;

		ImageQueue.push_back(Draw);
	}

	bool CGUIManager::IsMouseCaptured() const
	{
		return PlatformImplementation->IsMouseCaptured;
	}

	IEventListener * CGUIManager::GetEventRoot()
	{
		return EventRoot;
	}

}
