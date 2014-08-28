
#pragma once

#include <ionGL.h>
#include <ionAsset.h>

class CScene;
class ILightSceneNode;
class IRenderPass;


class CDrawManager
{

public:

	CDrawManager();

	virtual void Draw(CScene * Scene);

	virtual ion::GL::Uniform * GetUniform(string const & Label);

	virtual void RegisterLight(ILightSceneNode * Light);

private:

	vector<ILightSceneNode *> RegisteredLights;

	CUniformValue<glm::mat4> View;
	CUniformValue<glm::mat4> Proj;
	CUniformValue<vec3f> CameraPosition;

	struct SLightBinding
	{
		CUniformValue<vec3f> * Position = new CUniformValue<vec3f>{};
		CUniformValue<color3f> * Color = new CUniformValue<color3f>{};
		CUniformValue<f32> * Radius = new CUniformValue<f32>{};
	};

	vector<SLightBinding> LightBindings;
	CUniformValue<uint> LightCount = 0;

};
