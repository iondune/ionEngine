#ifndef _CABBAGECOLLIDER_CSCENEEFFECTMANAGER_H_INCLUDED_
#define _CABBAGECOLLIDER_CSCENEEFFECTMANAGER_H_INCLUDED_

#include <vector>
#include <map>

#include "CFrameBufferObject.h"
#include "ISceneObject.h"

enum ESceneEffect
{
	ESE_ALL = 0,
	ESE_SSAO = 1,
	ESE_SSAO_BLUR = 2,
	ESE_BLOOM = 4,
	ESE_HEAT_WAVE = 8,
	ESE_WATER_DISTORT = 16
};

class CSceneManager;

class CSceneEffectManager
{

protected:

	CSceneManager * SceneManager;

	int EnabledEffects;

	// SSAO Stuff
	CFrameBufferObject * NormalPassTarget;
	CTexture * NormalPassTexture;

	CFrameBufferObject * SSAOResultTarget;
	CTexture * SSAOResultTexture;

	CTexture * RandomNormalsTexture;
	CShader * SSAOShader;


	// Blur Shaders
	CShader * BlurVertical, * BlurHorizontal;

	// Bloom Stuff
	CFrameBufferObject * BloomResultTarget;
	CTexture * BloomResultTexture;


	// Blending
	CShader * BlendShader;
	CShader * QuadCopy;
	CTexture * Magenta, * White, * Black;

	CFrameBufferObject * ScratchTarget1;
	CTexture * ScratchTexture1;

	CTexture * HeatOffsetTexture;
	CShader * HeatCopy;

	CTexture * WaterOffsetTexture;

	float Timer;

public:

	CSceneEffectManager(CSceneManager * sceneManager);

	class SRenderPass
	{

	public:

		CFrameBufferObject * Target;
		ERenderPass Pass;

		SRenderPass();

		bool const operator == (SRenderPass const & rhs);
	
	};

	class SPostProcessPass
	{

	public:
		
		SPostProcessPass();

		CShader * Shader;
		CFrameBufferObject * Target;

		std::map<std::string, float> Floats;
		std::map<std::string, int> Ints;
		std::map<std::string, CTexture *> Textures;
		std::map<std::string, SColor> Colors;

		void doPass();

		void begin();
		void end();

		bool SetTarget;

		CShaderContext * Context;

	};

	std::vector<SRenderPass> RenderPasses;

	virtual void apply();

	virtual void setEffectEnabled(ESceneEffect const Effect, bool const Enabled);
	virtual bool const isEffectEnabled(ESceneEffect const Effect);

};

#endif
