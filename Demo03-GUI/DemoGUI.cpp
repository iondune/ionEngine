
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsGL.h>
#include <ionGUI.h>

using namespace ion;


int main()
{
	SingletonPointer<CGraphicsAPI> GraphicsAPI;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CGUIManager> GUIManager;

	GraphicsAPI->Init(new Graphics::COpenGLImplementation());
	WindowManager->Init(GraphicsAPI);

	CWindow * Window = WindowManager->CreateWindow(vec2i(1280, 1024), "ionEngine GUI Demo", EWindowType::Windowed);
	SharedPointer<Graphics::IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<Graphics::IRenderTarget> RenderTarget = Context->GetBackBuffer();
	RenderTarget->SetClearColor(color3f(0.3f));

	GUIManager->Init(Window);
	GUIManager->AddFontFromFile("OpenSans.ttf", 18.f);
	Window->AddListener(GUIManager);

	while (WindowManager->Run())
	{
		RenderTarget->ClearColorAndDepth();

		GUIManager->NewFrame();
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow();
		}
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 100), Colors::White, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 120), Colors::Red, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 140), Colors::Orange, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 160), Colors::Yellow, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 180), Colors::Green, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 200), Colors::Cyan, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 220), Colors::Blue, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 240), Colors::Magenta, "Hello, world!");
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + vec2i(100, 260), Colors::Black, "Hello, world!");
		GUIManager->Draw();

		Window->SwapBuffers();
	}

	GUIManager->Shutdown();

	return 0;
}
