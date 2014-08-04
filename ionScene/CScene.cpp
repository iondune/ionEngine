
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

void CScene::DrawAll(IGraphicsEngine * Engine)
{
	Engine->Begin(this);
	Root->Update();
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
		{
			View.Value = ActiveCamera->GetViewMatrix();
			return & View;
		}
		else
			cerr << "Error! No bound camera" << endl;
	}
	else if (Label == "Projection")
	{
		if (ActiveCamera)
		{
			View.Value = ActiveCamera->GetProjectionMatrix();
			return & View;
		}
		else
			cerr << "Error! No bound camera" << endl;
	}

	return nullptr;
}
