
#include <ionWindow.h>
#include <ionGraphicsD3D11.h>

using namespace ion;


int main()
{
	Log::AddDefaultOutputs();

	Log::Info("Info");
	Log::Warn("Warning");
	Log::Error("Error");

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CGraphicsAPI> GraphicsAPI;

	GraphicsAPI->Init(new Graphics::CD3D11Implementation());
	WindowManager->Init(GraphicsAPI);
	WindowManager->CreateWindow(vec2i(640, 480), "DemoWindowManager", EWindowType::Windowed);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();
	}

	return 0;
}
