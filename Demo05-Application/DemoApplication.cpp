
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsGL.h>
#include <ionScene.h>
#include <ionApplication.h>

using namespace ion;
using namespace ion::Scene;
using namespace ion::Graphics;


IShaderProgram * LoadShader(IGraphicsAPI * GraphicsAPI, string const & Name)
{
	string const ShaderDirectory = "Assets/Shaders/";

	IVertexShader * VertexShader = GraphicsAPI->CreateVertexShaderFromFile(ShaderDirectory + Name + ".vert");
	IPixelShader * PixelShader = GraphicsAPI->CreatePixelShaderFromFile(ShaderDirectory + Name + ".frag");

	if (! VertexShader)
	{
		Log::Error("Failed to compile vertex shader '%s'", Name);
		return nullptr;
	}

	if (! PixelShader)
	{
		Log::Error("Failed to compile pixel shader '%s'", Name);
		return nullptr;
	}

	IShaderProgram * ShaderProgram = GraphicsAPI->CreateShaderProgram();
	ShaderProgram->SetVertexStage(VertexShader);
	ShaderProgram->SetPixelStage(PixelShader);

	return ShaderProgram;
}


int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CTimeManager> TimeManager;
	SingletonPointer<CSceneManager> SceneManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "DemoApplication", EWindowType::Windowed);
	TimeManager->Init();

	IGraphicsAPI * GraphicsAPI = new COpenGLAPI();


	/////////////////
	// Load Assets //
	/////////////////

	CSimpleMesh * SphereMesh = CGeometryCreator::CreateSphere();
	CSimpleMesh * SkySphereMesh = CGeometryCreator::CreateSkySphere();
	CSimpleMesh * PlaneMesh = CGeometryCreator::CreatePlane(vec2f(100.f));

	IShaderProgram * DiffuseShader = LoadShader(GraphicsAPI, "Diffuse");
	IShaderProgram * SimpleShader = LoadShader(GraphicsAPI, "Simple");
	IShaderProgram * SpecularShader = LoadShader(GraphicsAPI, "Specular");
	IShaderProgram * SkySphereShader = LoadShader(GraphicsAPI, "SkySphere");

	CImage * Image = CImage::Load("Assets/Images/SkyMap.jpg");
	ITexture2D * SkyMap = GraphicsAPI->CreateTexture2D(Image->GetSize(), ITexture::EMipMaps::True, ITexture::EFormatComponents::RGB, ITexture::EInternalFormatType::Fix8);
	SkyMap->Upload(Image->GetData(), Image->GetSize(), ITexture::EFormatComponents::RGB, EScalarType::UnsignedInt8);
	SkyMap->SetMagFilter(ITexture::EFilter::Nearest);


	////////////////////
	// ionScene Setup //
	////////////////////

	CRenderPass * RenderPass = new CRenderPass(GraphicsAPI);
	SceneManager->AddRenderPass(RenderPass);

	CPerspectiveCamera * Camera = new CPerspectiveCamera(Window->GetAspectRatio());
	Camera->SetPosition(vec3f(0, 3, -3));
	Camera->SetLookAtTarget(vec3f(0, 0, 0));
	Camera->SetFocalLength(0.4f);
	RenderPass->SetActiveCamera(Camera);

	IRenderTarget * RenderTarget = GraphicsAPI->GetWindowBackBuffer(Window);
	RenderTarget->SetClearColor(color3f(0.3f));

	CCameraController * Controller = new CCameraController(Camera);
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
	RenderPass->AddSceneObject(SpecularSphere);

	CSimpleMeshSceneObject * PlaneObject = new CSimpleMeshSceneObject();
	PlaneObject->SetMesh(PlaneMesh);
	PlaneObject->SetShader(DiffuseShader);
	RenderPass->AddSceneObject(PlaneObject);

	CSimpleMeshSceneObject * SkySphereObject = new CSimpleMeshSceneObject();
	SkySphereObject->SetMesh(SkySphereMesh);
	SkySphereObject->SetShader(SkySphereShader);
	SkySphereObject->SetTexture("uTexture", SkyMap);
	RenderPass->AddSceneObject(SkySphereObject);

	CPointLight * Light1 = new CPointLight();
	Light1->SetPosition(vec3f(0, 1, 0));
	Light1->SetColor(Colors::Red);
	RenderPass->AddLight(Light1);

	CPointLight * Light2 = new CPointLight();
	Light2->SetPosition(vec3f(4, 2, 0));
	Light2->SetColor(Colors::Green);
	RenderPass->AddLight(Light2);

	CPointLight * Light3 = new CPointLight();
	Light3->SetPosition(vec3f(12, 3, 0));
	Light3->SetColor(Colors::Blue);
	RenderPass->AddLight(Light3);


	///////////////
	// Main Loop //
	///////////////

	TimeManager->Init();
	while (WindowManager->Run())
	{
		TimeManager->Update();

		float const Radius = ((f32) Sin(TimeManager->GetRunTime()) / 2.f + 0.5f) * 10.f;
		Light1->SetRadius(Radius);
		Light2->SetRadius(Radius);
		Light3->SetRadius(Radius);

		SkySphereObject->SetPosition(Camera->GetPosition());

		RenderTarget->ClearColorAndDepth();
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
