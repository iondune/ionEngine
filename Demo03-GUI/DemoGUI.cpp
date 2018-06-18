
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsD3D11.h>
#include <ionGUI.h>

using namespace ion;


int main()
{
	SingletonPointer<CGraphicsAPI> GraphicsAPI;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CGUIManager> GUIManager;

	Graphics::CD3D11Implementation * GraphicsImplementation = new Graphics::CD3D11Implementation();
	GraphicsAPI->Init(GraphicsImplementation);
	WindowManager->Init(GraphicsAPI);

	CWindow * Window = WindowManager->CreateWindow(vec2i(1280, 1024), "ionEngine GUI Demo", EWindowType::Windowed);
	SharedPointer<Graphics::IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<Graphics::IRenderTarget> RenderTarget = Context->GetBackBuffer();
	RenderTarget->SetClearColor(color3f(0.3f));

	GUIManager->Init(Window, GraphicsImplementation);
	Window->AddListener(GUIManager);

	while (WindowManager->Run())
	{
		RenderTarget->ClearColorAndDepth();

		GUIManager->NewFrame();
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowDemoWindow();
		}
		GUIManager->Text(vec2i(100, 100), Color::Basic::White, "Hello, world!");
		GUIManager->Text(vec2i(100, 120), Color::Basic::Red, "Hello, world!");
		GUIManager->Text(vec2i(100, 140), Color::Basic::Orange, "Hello, world!");
		GUIManager->Text(vec2i(100, 160), Color::Basic::Yellow, "Hello, world!");
		GUIManager->Text(vec2i(100, 180), Color::Basic::Green, "Hello, world!");
		GUIManager->Text(vec2i(100, 200), Color::Basic::Cyan, "Hello, world!");
		GUIManager->Text(vec2i(100, 220), Color::Basic::Blue, "Hello, world!");
		GUIManager->Text(vec2i(100, 240), Color::Basic::Magenta, "Hello, world!");
		GUIManager->Text(vec2i(100, 260), Color::Basic::Black, "Hello, world!");
		GUIManager->Draw();

		Window->SwapBuffers();
	}

	GUIManager->Shutdown();

	return 0;
}
