
#pragma once

#include "ICamera.h"
#include "CDrawManager.h"


class CScene
{

public:

	CScene();

	virtual ICamera * const GetActiveCamera();
	virtual ICamera const * const GetActiveCamera() const;
	virtual void SetActiveCamera(ICamera * const activeCamera);

	virtual void DrawAll(CDrawManager * Engine, CRenderPassManager * RenderPassManager);

	virtual ISceneNode * GetRoot();

protected:

	ICamera * ActiveCamera = nullptr;
	ISceneNode * Root = new ISceneNode{nullptr};

};
