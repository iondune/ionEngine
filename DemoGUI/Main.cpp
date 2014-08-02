
#include <ionWindow.h>
#include <ionGL.h>
#include <ionGUI.h>

using namespace ion::GL;


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	freetype::font_data Font;
	Font.init("OpenSans.ttf", 12);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Context::Clear({ EBuffer::Color, EBuffer::Depth });
		
		freetype::print(Font, 0, 0, "Hello from 0, 0");
		freetype::print(Font, 0, 480, "Hello from 0, 480");
		freetype::print(Font, 0, 240, "Hello from 0, 240");

		Window->SwapBuffers();
	}

	return 0;
}
