
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>
#include <ionScene.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	SceneManager->GetMeshLibrary()->Add("Sphere", CGeometryCreator::CreateSphere());
	SceneManager->GetShaderLibrary()->Load("Diffuse");
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Diffuse");


	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
