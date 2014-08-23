
#pragma once

#include <ionGL.h>
#include <ionAsset.h>

class CScene;
class ILightSceneNode;


class CDrawManager : public Singleton<CDrawManager>
{

public:


	CDrawManager();

	virtual void Begin(CScene * Scene);
	virtual void Update();
	virtual void Draw(map<CShader *, vector<CDrawConfig *>> const & Configurations);
	virtual void Finalize();

	virtual ion::GL::Uniform * GetUniform(string const & Label);

	virtual void RegisterLight(ILightSceneNode * Light);

private:

	CScene * CurrentScene = nullptr;
	
	typedef map<CShader *, vector<CDrawConfig *>> RenderPass;
	vector<RenderPass> RenderPasses;
	vector<ILightSceneNode *> RegisteredLights;

	CUniformValue<glm::mat4> View;
	CUniformValue<glm::mat4> Proj;

	struct SLightBinding
	{
		CUniformValue<vec3f> * Position = new CUniformValue<vec3f>{};
		CUniformValue<color3f> * Color = new CUniformValue<color3f>{};
		CUniformValue<f32> * Radius = new CUniformValue<f32>{};
	};

	vector<SLightBinding> LightBindings;
	CUniformValue<uint> LightCount = 0;

};
