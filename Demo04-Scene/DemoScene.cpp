
#include <ionWindow.h>
#include <ionGraphics.h>
#include <ionGraphicsGL.h>
#include <ionScene.h>

using namespace ion;
using namespace Scene;
using namespace Graphics;


int main()
{
	////////////////////
	// ionEngine Init //
	////////////////////

	Log::AddDefaultOutputs();

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;

	WindowManager->Init();
	CWindow * Window = WindowManager->CreateWindow(vec2i(640, 480), "DemoScene", EWindowType::Windowed);


	IGraphicsAPI * GraphicsAPI = new COpenGLAPI();

	CSimpleMesh * Mesh = CGeometryCreator::CreateSphere();
	IVertexShader * VertexShader = GraphicsAPI->CreateVertexShaderFromFile("Diffuse.vert");
	IPixelShader * PixelShader = GraphicsAPI->CreatePixelShaderFromFile("Diffuse.frag");

	if (! VertexShader)
		std::cerr << "Failed to compile vertex shader!" << std::endl;

	if (! PixelShader)
		std::cerr << "Failed to compile pixel shader!" << std::endl;

	IShaderProgram * ShaderProgram = GraphicsAPI->CreateShaderProgram();
	ShaderProgram->SetVertexStage(VertexShader);
	ShaderProgram->SetPixelStage(PixelShader);

	CRenderPass * RenderPass = new CRenderPass(GraphicsAPI);
	SceneManager->AddRenderPass(RenderPass);

	CSimpleMeshSceneObject * SceneObject = new CSimpleMeshSceneObject();
	SceneObject->SetMesh(Mesh);
	SceneObject->SetShader(ShaderProgram);
	RenderPass->AddSceneObject(SceneObject);

	CPerspectiveCamera * Camera = new CPerspectiveCamera();
	Camera->SetPosition(vec3f(0, 0, -3));
	RenderPass->SetActiveCamera(Camera);

	while (WindowManager->Run())
	{
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
