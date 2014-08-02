
#include <ionWindow.h>
#include <ionGL.h>
#include <ionGUI.h>

using namespace ion::GL;


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	IFont * Font = IFont::init("OpenSans.ttf", 12);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Context::Clear({ EBuffer::Color, EBuffer::Depth });
		
		Font->print(0, 0, "Hello from 0, 0");
		Font->print(320, 0, "Hello from 320, 0");
		Font->print(0, 240, "Hello from 0, 240");
		Font->print(320, 240, "Hello from 320, 240\nWith multiple lines!");
		Font->print(0, 480, "Hello from 0, 480");

		Window->SwapBuffers();
	}

	delete Font;

	return 0;
}
