
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestGL", EWindowType::Windowed);

	SceneManager->MeshLibrary->Add("Sphere", CGeometryCreator::CreateSphere());
	SceneManager->ShaderLibrary->Load("Diffuse");
	SceneManager->Factory->AddMeshNode("Sphere", "Diffuse");


	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
