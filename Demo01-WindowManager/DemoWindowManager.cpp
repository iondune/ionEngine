
#include <ionWindow.h>
#include <ionGraphicsGL.h>

using namespace ion;


int main()
{
	Log::AddDefaultOutputs();

	Log::Info("Info");
	Log::Warn("Warning");
	Log::Error("Error");

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CGraphicsAPI> GraphicsAPI;

	GraphicsAPI->Init(new Graphics::COpenGLImplementation());
	WindowManager->Init(GraphicsAPI);
	WindowManager->CreateWindow(vec2i(640, 480), "TestWindowManager", EWindowType::Windowed);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();
	}

	return 0;
}
