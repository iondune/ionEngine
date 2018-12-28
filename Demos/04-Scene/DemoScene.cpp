
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsD3D11.h>
#include <ionScene.h>

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
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CTimeManager> TimeManager;

	GraphicsAPI->Init(new Graphics::CD3D11Implementation());
	WindowManager->Init(GraphicsAPI);
	TimeManager->Init(WindowManager);
	SceneManager->Init(GraphicsAPI);

	CWindow * Window = WindowManager->CreateWindow(vec2i(1600, 900), "DemoScene", EWindowType::Windowed);
	SharedPointer<IGraphicsContext> Context = GraphicsAPI->GetWindowContext(Window);
	SharedPointer<IRenderTarget> RenderTarget = Context->GetBackBuffer();
	RenderTarget->SetClearColor(color3f(0.3f));


	///////////////////
	// Create Shader //
	///////////////////

	SharedPointer<IVertexStage> VertexShader = GraphicsAPI->CreateVertexStageFromFile("Diffuse.hlsl");
	SharedPointer<IPixelStage> PixelShader = GraphicsAPI->CreatePixelStageFromFile("Diffuse.hlsl");

	if (! VertexShader)
		std::cerr << "Failed to compile diffuse vertex shader!" << std::endl;

	if (! PixelShader)
		std::cerr << "Failed to compile diffuse pixel shader!" << std::endl;

	SharedPointer<IShader> DiffuseProgram = GraphicsAPI->CreateShaderProgram();
	DiffuseProgram->SetVertexStage(VertexShader);
	DiffuseProgram->SetPixelStage(PixelShader);

	VertexShader = GraphicsAPI->CreateVertexStageFromFile("Axis.hlsl");
	PixelShader = GraphicsAPI->CreatePixelStageFromFile("Axis.hlsl");

	if (! VertexShader)
		std::cerr << "Failed to compile axis vertex shader!" << std::endl;

	if (! PixelShader)
		std::cerr << "Failed to compile axis pixel shader!" << std::endl;

	SharedPointer<IShader> AxisProgram = GraphicsAPI->CreateShaderProgram();
	AxisProgram->SetVertexStage(VertexShader);
	AxisProgram->SetPixelStage(PixelShader);


	////////////////////
	// ionScene Setup //
	////////////////////

	CRenderPass * RenderPass = new CRenderPass(Context);
	RenderPass->SetRenderTarget(RenderTarget);
	SceneManager->AddRenderPass(RenderPass);

	CPerspectiveCamera * Camera = new CPerspectiveCamera(Window->GetAspectRatio());
	Camera->SetFocalLength(0.4f);
	RenderPass->SetActiveCamera(Camera);


	///////////////////
	// Scene Objects //
	///////////////////

	CSimpleMesh * Mesh1 = CGeometryCreator::CreateSphere();
	CSimpleMeshSceneObject * SceneObject1 = new CSimpleMeshSceneObject();
	SceneObject1->SetMesh(Mesh1);
	SceneObject1->SetShader(DiffuseProgram);
	SceneObject1->SetPosition(vec3f(2, 0.5f, 0));
	RenderPass->AddSceneObject(SceneObject1);

	CSimpleMesh * Mesh2 = CGeometryCreator::CreateCylinder(0.6f, 0.3f);
	CSimpleMeshSceneObject * SceneObject2 = new CSimpleMeshSceneObject();
	SceneObject2->SetMesh(Mesh2);
	SceneObject2->SetShader(DiffuseProgram);
	SceneObject2->SetPosition(vec3f(0, 0, -2));
	SceneObject2->SetRotation(vec3f(-Constants32::Pi / 2, 0, 0));
	RenderPass->AddSceneObject(SceneObject2);

	CSimpleMesh * Mesh3 = CGeometryCreator::CreateCube();
	CSimpleMeshSceneObject * SceneObject3 = new CSimpleMeshSceneObject();
	SceneObject3->SetMesh(Mesh3);
	SceneObject3->SetShader(DiffuseProgram);
	SceneObject3->SetPosition(vec3f(-2, 0.5f, 0));
	RenderPass->AddSceneObject(SceneObject3);
	
	CCoordinateFrameSceneObject * SceneAxis = new CCoordinateFrameSceneObject();
	SceneAxis->SetShader(AxisProgram);
	RenderPass->AddSceneObject(SceneAxis);


	///////////////
	// Main Loop //
	///////////////

	TimeManager->Start();
	while (WindowManager->Run())
	{
		TimeManager->Update();
		float const Time = (float) TimeManager->GetRunTime();
		Camera->SetPosition(vec3f(sin(Time) * 4, 2, cos(Time) * 4));
		Camera->SetLookAtTarget(vec3f(0, 0, 0));

		RenderTarget->ClearColorAndDepth();
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
