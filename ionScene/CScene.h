
#pragma once

#include "ICamera.h"
#include "IGraphicsEngine.h"


class CScene
{

public:

	CScene();

	virtual ICamera * const GetActiveCamera();
	virtual ICamera const * const GetActiveCamera() const;
	virtual void SetActiveCamera(ICamera * const activeCamera);

	virtual void DrawAll(IGraphicsEngine * Engine);

	ISceneNode * GetRoot();
	ion::GL::Uniform * GetUniform(string const & Label);

protected:

	ICamera * ActiveCamera = nullptr;
	ISceneNode * Root = new ISceneNode{nullptr};

};
