
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

	GUIManager->Init(Window, true);
	GUIManager->AddFontFromFile("OpenSans.ttf", 18.f);
	Window->AddListener(GUIManager);

	IGraphicsAPI * GraphicsAPI = new COpenGLAPI();
	SharedPtr<IRenderTarget> RenderTarget = GraphicsAPI->GetWindowBackBuffer(Window);
	RenderTarget->SetClearColor(color3f(0.3f));

	while (WindowManager->Run())
	{
		RenderTarget->ClearColorAndDepth();

		GUIManager->NewFrame();
		{
			ImGui::Text("Hello, world!");
		}
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
			ImGui::ShowTestWindow();
		}
		ImGui::Render();

		Window->SwapBuffers();
	}

	GUIManager->Shutdown();

	return 0;
}
