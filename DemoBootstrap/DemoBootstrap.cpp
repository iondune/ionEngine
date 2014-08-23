
#include <ionWindow.h>
#include <ionGL.h>
#include <ionAsset.h>
#include <ionScene.h>
#include <ionBootstrap.h>


int main()
{
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CDrawManager> GraphicsEngine;
	SingletonPointer<CTimeManager> TimeManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "TestBootstrap", EWindowType::Windowed);
	
	SceneManager->GetTextureLibrary()->SetBaseDirectory("Assets/Images");
	SceneManager->GetShaderLibrary()->SetBaseDirectory("Assets/Shaders");
	
	SceneManager->GetMeshLibrary()->Add("Sphere", CGeometryCreator::CreateSphere());
	SceneManager->GetMeshLibrary()->Add("Plane", CGeometryCreator::CreatePlane(vec2f(100.f)));
	SceneManager->GetShaderLibrary()->Load("Diffuse");
	SceneManager->GetShaderLibrary()->Load("Simple");
	SceneManager->GetShaderLibrary()->Load("Normals");
	SceneManager->GetTextureLibrary()->Load("SkyMap.jpg")->SetMagFilter(ion::GL::Texture::EFilter::Nearest);

	SceneManager->GetFactory()->AddMeshNode("Sphere", "Simple")->SetPosition(vec3f(0, 1, 0));
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Simple")->SetPosition(vec3f(4, 2, 0));
	SceneManager->GetFactory()->AddMeshNode("Sphere", "Simple")->SetPosition(vec3f(12, 3, 0));
	SceneManager->GetFactory()->AddMeshNode("Plane", "Diffuse");
	SceneManager->GetFactory()->AddSkySphereNode("SkyMap.jpg");
	ILightSceneNode * Light1 = SceneManager->GetFactory()->AddLight(vec3f(0, 1, 0));
	ILightSceneNode * Light2 = SceneManager->GetFactory()->AddLight(vec3f(4, 2, 0));
	ILightSceneNode * Light3 = SceneManager->GetFactory()->AddLight(vec3f(12, 3, 0));

	ICamera * Camera = nullptr;
	SceneManager->GetScene()->SetActiveCamera(Camera = SceneManager->GetFactory()->AddPerspectiveCamera(Window->GetAspectRatio()));
	Camera->SetPosition(vec3f(0, 3, -3));

	CCameraController * Controller = new CCameraController{Camera};
	Window->AddListener(Controller);
	TimeManager->MakeUpdateTick(0.02)->AddListener(Controller);
	
	ion::GL::Context::Init();
	TimeManager->Init();
	while (! WindowManager->ShouldClose())
	{
		WindowManager->PollEvents();
		TimeManager->Update();
		
		float Radius = 1.f;(Sin(TimeManager->GetRunTime()) / 2.f + 0.5f) * 10.f;
		Light1->SetRadius(Radius);
		Light2->SetRadius(Radius);
		Light3->SetRadius(Radius);

		SceneManager->DrawAll(GraphicsEngine.Get());
		Window->SwapBuffers();
	}

	return 0;
}
