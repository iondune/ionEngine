
#pragma once

#include "ICamera.h"
#include "CMeshLibrary.h"
#include "CShaderLibrary.h"
#include "CSceneNodeFactory.h"


class CSceneManager : public Singleton<CSceneManager>
{

public:

	virtual ICamera * const GetActiveCamera();
	virtual ICamera const * const GetActiveCamera() const;
	virtual void SetActiveCamera(ICamera * const activeCamera);

	virtual void DrawAll();

	CMeshLibrary * GetMeshLibrary();
	CShaderLibrary * GetShaderLibrary();
	CSceneNodeFactory * GetFactory();
	ISceneNode * GetRoot();

protected:

	ICamera * ActiveCamera = nullptr;
	CMeshLibrary * MeshLibrary = new CMeshLibrary;
	CShaderLibrary * ShaderLibrary = new CShaderLibrary;
	CSceneNodeFactory * Factory = new CSceneNodeFactory{this};
	ISceneNode * Root = new ISceneNode{nullptr};

private:

	friend class Singleton<CSceneManager>;
	CSceneManager();

};
