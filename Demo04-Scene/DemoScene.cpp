
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


	ICamera * Camera = nullptr;
	//SceneManager->GetScene()->SetActiveCamera(Camera = SceneManager->GetFactory()->AddPerspectiveCamera((Window->GetAspectRatio())));
	//Camera->SetPosition(vec3f(0, 0, -3));

	//ion::GL::Context::Init();
	while (WindowManager->Run())
	{
		SceneManager->DrawAll();
		Window->SwapBuffers();
	}

	return 0;
}
