
#pragma once

#include <ionGL.h>
#include <ionAsset.h>

class CScene;


class CDrawManager : public Singleton<CDrawManager>
{

public:


	CDrawManager();

	void Begin(CScene * Scene);
	void Update();
	void Draw(map<CShader *, vector<CDrawConfig *>> const & Configurations);
	void Finalize();
	virtual ion::GL::Uniform * GetUniform(string const & Label);

private:

	CScene * CurrentScene = nullptr;
	
	typedef map<CShader *, vector<CDrawConfig *>> RenderPass;
	vector<RenderPass> RenderPasses;

	ion::GL::UniformValue<glm::mat4> View;
	ion::GL::UniformValue<glm::mat4> Proj;

	struct SLightBinding
	{
		CUniformValue<vec3f> * Position = new CUniformValue<vec3f>{};
		CUniformValue<color3f> * Color = new CUniformValue<color3f>{};
		CUniformValue<f32> * Radius = new CUniformValue<f32>{};
	};

	vector<SLightBinding> LightBindings;

};
