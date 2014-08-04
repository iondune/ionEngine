
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

	virtual void Update();
	virtual void DrawAll(IGraphicsEngine * Engine);

	ISceneNode * GetRoot();
	ion::GL::Uniform * GetUniform(string const & Label);

protected:

	ICamera * ActiveCamera = nullptr;
	ISceneNode * Root = new ISceneNode{nullptr};
	ion::GL::UniformValue<glm::mat4> View;
	ion::GL::UniformValue<glm::mat4> Proj;

};
