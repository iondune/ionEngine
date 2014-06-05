
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
	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "TestScene", EWindowType::Windowed);

	SceneManager->GetMeshLibrary()->Add("Sphere", CGeometryCreator::CreateSphere());
	SceneManager->GetShaderLibrary()->Load("Diffuse");
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Diffuse");
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Diffuse")->SetPosition(vec3f(1, 0, 0));

	CImage * Image = CImage::Load("Assets/Images/SkyMap.jpg");
	ion::GL::Texture2D * Texture = new ion::GL::Texture2D;
	Texture->Storage(Image->GetSize());
	Texture->Image(Image->GetData());
	SceneManager->GetFactory()->AddSkySphereNode(Texture);

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
		WindowManager->PollEvents();
		TimeManager->Update();
		SceneManager->DrawAll(GraphicsEngine.Get());
		Window->SwapBuffers();
	}

	return 0;
}
