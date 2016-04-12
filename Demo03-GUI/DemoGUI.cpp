
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsGL.h>
#include <ionGUI.h>

using namespace ion::Graphics;


int main()
{
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CGUIManager> GUIManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(1280, 1024), "ionEngine GUI Demo", EWindowType::Windowed);

	IGraphicsAPI * GraphicsAPI = new COpenGLAPI();
	SharedPointer<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<IRenderTarget> RenderTarget = Context->GetBackBuffer();
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
		GUIManager->Text(vec2i(Window->GetCursorLocation()) + 100, "Hello, world!");
		GUIManager->Draw();

		Window->SwapBuffers();
	}

	GUIManager->Shutdown();

	return 0;
}
