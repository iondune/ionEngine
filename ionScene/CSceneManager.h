
#pragma once

#include "CMeshLibrary.h"
#include "CShaderLibrary.h"
#include "CSceneNodeFactory.h"
#include "CScene.h"


class CSceneManager : public Singleton<CSceneManager>
{

public:

	CMeshLibrary * GetMeshLibrary();
	CShaderLibrary * GetShaderLibrary();
	CSceneNodeFactory * GetFactory();

	virtual void DrawAll(IGraphicsEngine * Engine);

	CScene * GetScene();
	ISceneNode * GetRoot();

protected:

	CMeshLibrary * MeshLibrary = new CMeshLibrary;
	CShaderLibrary * ShaderLibrary = new CShaderLibrary;
	CSceneNodeFactory * Factory = new CSceneNodeFactory{this};
	CScene * Scene = new CScene{};

private:

	friend class Singleton<CSceneManager>;
	CSceneManager();

};
