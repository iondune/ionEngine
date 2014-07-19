
#pragma once

#include <ionGL.h>
#include "IGraphicsEngine.h"
#include "CScene.h"


class CGLGraphicsEngine : public IGraphicsEngine, public Singleton<CGLGraphicsEngine>
{

public:

	struct SDrawDefinition
	{
		ion::GL::VertexArray * Array = 0;
		map<string, ion::GL::Uniform *> Uniforms;
		vector<ion::GL::ImageTexture *> Textures;

		SDrawDefinition();
		SDrawDefinition(ion::GL::VertexArray * Array);

		SDrawDefinition & AddUniform(string const & Label, IUniform * Uniform);
		SDrawDefinition & AddUniform(string const & Label, IUniform & Uniform);
		ion::GL::Uniform * GetUniform(string const & Label);
	};

	struct SRenderPass
	{
		map<CShader *, vector<SDrawDefinition>> Elements;
	};


	CGLGraphicsEngine();

	void Begin(CScene * Scene);
	void Draw(ISceneNode * Node);
	void Finalize(CScene * Scene);


	vector<SRenderPass> RenderPasses;

};
