
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsD3D11.h>
#include <ionScene.h>
#include <ionApplication.h>

using namespace ion;
using namespace ion::Scene;
using namespace ion::Graphics;


int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CGraphicsAPI> GraphicsAPI;
	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CTimeManager> TimeManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CAssetManager> AssetManager;

	GraphicsAPI->Init(new Graphics::CD3D11Implementation());
	WindowManager->Init(GraphicsAPI);
	TimeManager->Init(WindowManager);
	SceneManager->Init(GraphicsAPI);
	AssetManager->Init(GraphicsAPI);

	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "DemoApplication", EWindowType::Windowed);

	AssetManager->AddAssetPath("Assets");
	AssetManager->SetShaderPath("Shaders");
	AssetManager->SetTexturePath("Images");

	SharedPointer<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<IRenderTarget> RenderTarget = Context->GetBackBuffer();
	RenderTarget->SetClearColor(color3f(0.1f, 0.2f, 0.3f));


	/////////////////
	// Load Assets //
	/////////////////

	CSimpleMesh * SphereMesh = CGeometryCreator::CreateSphere();
	CSimpleMesh * SkyBoxMesh = CGeometryCreator::CreateCube();
	CSimpleMesh * PlaneMesh = CGeometryCreator::CreatePlane(vec2f(100.f));

	SharedPointer<IShader> DiffuseShader = AssetManager->LoadShader("Diffuse");
	SharedPointer<IShader> SimpleShader = AssetManager->LoadShader("Simple");
	SharedPointer<IShader> SpecularShader = AssetManager->LoadShader("Specular");


	////////////////////
	// ionScene Setup //
	////////////////////

	CRenderPass * RenderPass = new CRenderPass(Context);
	RenderPass->SetRenderTarget(RenderTarget);
	SceneManager->AddRenderPass(RenderPass);

	CPerspectiveCamera * Camera = new CPerspectiveCamera(Window->GetAspectRatio());
	Camera->SetPosition(vec3f(0, 3, -5));
	Camera->SetFocalLength(0.4f);
	RenderPass->SetActiveCamera(Camera);

	CCameraController * Controller = new CCameraController(Camera);
	Controller->SetTheta(15.f * Constants32::Pi / 48.f);
	Controller->SetPhi(-Constants32::Pi / 16.f);
	Window->AddListener(Controller);
	TimeManager->MakeUpdateTick(0.02)->AddListener(Controller);


	/////////////////
	// Add Objects //
	/////////////////

	CSimpleMeshSceneObject * LightSphere1 = new CSimpleMeshSceneObject();
	LightSphere1->SetMesh(SphereMesh);
	LightSphere1->SetShader(SimpleShader);
	LightSphere1->SetPosition(vec3f(0, 1, 0));
	RenderPass->AddSceneObject(LightSphere1);

	CSimpleMeshSceneObject * LightSphere2 = new CSimpleMeshSceneObject();
	LightSphere2->SetMesh(SphereMesh);
	LightSphere2->SetShader(SimpleShader);
	LightSphere2->SetPosition(vec3f(4, 2, 0));
	RenderPass->AddSceneObject(LightSphere2);

	CSimpleMeshSceneObject * LightSphere3 = new CSimpleMeshSceneObject();
	LightSphere3->SetMesh(SphereMesh);
	LightSphere3->SetShader(SimpleShader);
	LightSphere3->SetPosition(vec3f(12, 3, 0));
	RenderPass->AddSceneObject(LightSphere3);

	CSimpleMeshSceneObject * SpecularSphere = new CSimpleMeshSceneObject();
	SpecularSphere->SetMesh(SphereMesh);
	SpecularSphere->SetShader(SpecularShader);
	SpecularSphere->SetPosition(vec3f(3, 3, 6));
	SpecularSphere->GetMaterial().Ambient = vec3f(0.05f);
	RenderPass->AddSceneObject(SpecularSphere);

	CSimpleMeshSceneObject * PlaneObject = new CSimpleMeshSceneObject();
	PlaneObject->SetMesh(PlaneMesh);
	PlaneObject->SetShader(DiffuseShader);
	PlaneObject->GetMaterial().Ambient = vec3f(0.05f, 0.05f, 0.1f);
	RenderPass->AddSceneObject(PlaneObject);

	CPointLight * Light1 = new CPointLight();
	Light1->SetPosition(vec3f(0, 1, 0));
	Light1->SetColor(Color::Basic::Red);
	RenderPass->AddLight(Light1);

	CPointLight * Light2 = new CPointLight();
	Light2->SetPosition(vec3f(4, 2, 0));
	Light2->SetColor(Color::Basic::Green);
	RenderPass->AddLight(Light2);

	CPointLight * Light3 = new CPointLight();
	Light3->SetPosition(vec3f(12, 3, 0));
	Light3->SetColor(Color::Basic::Blue);
	RenderPass->AddLight(Light3);


	///////////////
	// Main Loop //
	///////////////

	TimeManager->Init(WindowManager);
	while (WindowManager->Run())
	{
		TimeManager->Update();

		float const MinimumBrightness = 0.2f;
		float const MaximumBrightness = 1.f - MinimumBrightness;
		float const Brightness = (Sin<float>((float) TimeManager->GetRunTime()) / 2.f + 0.5f) * MaximumBrightness + MinimumBrightness;
		float const Radius = Brightness * 10.f;
		Light1->SetRadius(Radius);
		Light2->SetRadius(Radius);
		Light3->SetRadius(Radius);

		float const Bright = 1;
		float const Dim = 0.5f;
		LightSphere1->GetMaterial().Diffuse = color3f(Bright, Dim, Dim) * Brightness;
		LightSphere2->GetMaterial().Diffuse = color3f(Dim, Bright, Dim) * Brightness;
		LightSphere3->GetMaterial().Diffuse = color3f(Dim, Dim, Bright) * Brightness;
		LightSphere1->SetScale(Brightness);
		LightSphere2->SetScale(Brightness);
		LightSphere3->SetScale(Brightness);

		RenderTarget->ClearColorAndDepth();
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
