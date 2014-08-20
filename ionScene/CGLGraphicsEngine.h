
#pragma once

#include <ionGL.h>
#include "IGraphicsEngine.h"
#include "CScene.h"


class CGLGraphicsEngine : public IGraphicsEngine, public Singleton<CGLGraphicsEngine>
{

public:

	typedef map<CShader *, vector<CDrawConfig *>> RenderPass;

	CGLGraphicsEngine();

	void Begin(CScene * Scene);
	void Draw(CScene * Scene, map<CShader *, vector<CDrawConfig *>> const & Configurations);
	void Finalize(CScene * Scene);


	vector<RenderPass> RenderPasses;

};
