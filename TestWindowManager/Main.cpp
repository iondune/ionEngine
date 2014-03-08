
#include <ionEngine.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;

	WindowManager->Init();
	WindowManager->CreateWindow(vec2i(640, 480), "TestWindowManager", false);

	while (! WindowManager->ShouldClose())
		WindowManager->PollEvents();

	return 0;
}
