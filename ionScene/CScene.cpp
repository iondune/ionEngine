
#include "CScene.h"


CScene::CScene()
{
}

ICamera * const CScene::GetActiveCamera()
{
	return ActiveCamera;
}

ICamera const * const CScene::GetActiveCamera() const
{
	return ActiveCamera;
}

void CScene::SetActiveCamera(ICamera * const activeCamera)
{
	ActiveCamera = activeCamera;
}

void CScene::Update()
{
	View.Value = ActiveCamera->GetViewMatrix();
	Proj.Value = ActiveCamera->GetProjectionMatrix();
}

void CScene::DrawAll(IGraphicsEngine * Engine)
{
	Engine->Begin(this);
	Root->Update();
	Update();
	Root->Draw(Engine);
	Engine->Finalize(this);
}

ISceneNode * CScene::GetRoot()
{
	return Root;
}

ion::GL::Uniform * CScene::GetUniform(string const & Label)
{
	if (Label == "View")
	{
		if (ActiveCamera)
			return & View;
		else
			cerr << "Error! No active camera" << endl;
	}
	else if (Label == "Projection")
	{
		if (ActiveCamera)
			return & Proj;
		else
			cerr << "Error! No active camera" << endl;
	}

	return nullptr;
}
