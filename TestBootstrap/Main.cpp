
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>
#include <ionScene.h>
#include <ionBootstrap.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CGLGraphicsEngine> GraphicsEngine;
	SingletonPointer<CTimeManager> TimeManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "TestScene", EWindowType::Windowed);

	SceneManager->GetMeshLibrary()->Add("Sphere", CGeometryCreator::CreateSphere());
	SceneManager->GetShaderLibrary()->Load("Diffuse");
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Diffuse");

	ICamera * Camera = nullptr;
	SceneManager->GetScene()->SetActiveCamera(Camera = SceneManager->GetFactory()->AddPerspectiveCamera(Window->GetAspectRatio()));
	Camera->SetPosition(vec3f(0, 0, -3));

	CCameraController * Controller = new CCameraController{Camera};
	Window->AddListener(Controller);
	TimeManager->MakeUpdateTick(0.02)->AddListener(Controller);
	
	ion::GL::Context::Init();
	TimeManager->Init();
	while (! WindowManager->ShouldClose())
	{
		TimeManager->Update();
		WindowManager->PollEvents();
		SceneManager->DrawAll(GraphicsEngine.Get());
		Window->SwapBuffers();
	}

	return 0;
}
