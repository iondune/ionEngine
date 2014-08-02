
#include <ionWindow.h>
#include <ionGL.h>
#include <ionGUI.h>

using namespace ion::GL;


void CheckSize(IFont * Font, char * str)
{
	int Width, Height;
	Font->measure(& Width, & Height, str);
	printf("'%s' is %d x %d\n", str, Width, Height);
}

int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	IFont * Font = IFont::init("OpenSans.ttf", 12);
	
	CheckSize(Font, "a");
	CheckSize(Font, "ab");
	CheckSize(Font, "abc");
	CheckSize(Font, "A");
	CheckSize(Font, "AB");
	CheckSize(Font, "ABC");

	CGUIManager * Manager = new CGUIManager();
	Manager->Init();

	CGUIEventManager * EventManager = new CGUIEventManager(Manager->GetCanvas(), Window);
	
	auto Control = new Gwen::Controls::WindowControl(Manager->GetCanvas());
	Control->SetTitle("Window");
	Control->SetBounds(30, 30, 150, 100);

	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();

		Context::Clear({ EBuffer::Color, EBuffer::Depth });

		Font->print(20, 20, "a\nab\nabc\nA\nAB\nABC");
		
		Font->print(0, 0, "Hello from 0, 0");
		Font->print(320, 0, "Hello from 320, 0");
		Font->print(0, 240, "Hello from 0, 240");
		Font->print(320, 240, "Hello from 320, 240\nWith multiple lines!");
		Font->print(0, 480, "Hello from 0, 480");

		Manager->Draw(0.01f);

		Window->SwapBuffers();
	}

	delete Font;

	return 0;
}
