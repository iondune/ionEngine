
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>
#include <ionScene.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CGLGraphicsEngine> GraphicsEngine;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestScene", EWindowType::Windowed);

	SceneManager->GetMeshLibrary()->Add("Sphere", CGeometryCreator::CreateSphere());
	SceneManager->GetShaderLibrary()->Load("Diffuse");
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Diffuse");

	SceneManager->GetScene()->SetActiveCamera(SceneManager->GetFactory()->AddPerspectiveCamera());


	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();
		SceneManager->DrawAll(GraphicsEngine.Get());
		Window->SwapBuffers();
	}

	return 0;
}
