#include "CSceneEffectManager.h"

#include "CSceneManager.h"
#include "CTextureLoader.h"
#include "CShaderLoader.h"

#include <algorithm>


CSceneEffectManager::SRenderPass::SRenderPass()
	: Pass(ERenderPass::Default)
{}

bool const CSceneEffectManager::SRenderPass::operator == (SRenderPass const & rhs)
{
	return Target == rhs.Target && Pass == rhs.Pass;
}


CSceneEffectManager::SPostProcessPass::SPostProcessPass()
	: Target(0), Shader(0), SetTarget(true)
{}

void CSceneEffectManager::SPostProcessPass::begin()
{
	if (SetTarget)
	{
		if (Target)
			Target->bind();
		else
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	}
	
	glDisable(GL_DEPTH_TEST);
	Context = new CShaderContext(* Shader);
}

void CSceneEffectManager::SPostProcessPass::end()
{
	if (! Context)
		begin();

	for (std::map<std::string, CTexture *>::iterator it = Textures.begin(); it != Textures.end(); ++ it)
		Context->bindTexture(it->first, it->second);

	for (std::map<std::string, float>::iterator it = Floats.begin(); it != Floats.end(); ++ it)
		Context->uniform(it->first, it->second);

	for (std::map<std::string, int>::iterator it = Ints.begin(); it != Ints.end(); ++ it)
		Context->uniform(it->first, it->second);

	for (std::map<std::string, SColor>::iterator it = Colors.begin(); it != Colors.end(); ++ it)
		Context->uniform(it->first, it->second);

	Context->bindBufferObject("aPosition", CSceneManager::getQuadHandle(), 2);

	glDrawArrays(GL_QUADS, 0, 4);

	if (SetTarget)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_DEPTH_TEST);

	delete Context;
}

void CSceneEffectManager::SPostProcessPass::doPass()
{
	begin();
	end();
}


CSceneEffectManager::CSceneEffectManager(CSceneManager * sceneManager)
	: EnabledEffects(0), SceneManager(sceneManager), NormalPassTarget(0), NormalPassTexture(0), RandomNormalsTexture(0),
	BlurHorizontal(0), BlurVertical(0), BlendShader(0), White(0), Black(0), Magenta(0),
	Timer(0.f)
{
	SSAOShader = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "SSAO.frag");
	BlendShader = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "Blend.frag");
	BlurVertical = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "BlurV.frag");
	BlurHorizontal = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "BlurH.frag");
	QuadCopy = CShaderLoader::loadShader("FBO/QuadCopy");
	HeatCopy = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "FBO/HeatCopy.frag");

	White = new CTexture(SColor(1.f, 1.f, 1.f));
	Black = new CTexture(SColor(0.f, 0.f, 0.f));
	Magenta = new CTexture(SColor(1.f, 0.f, 1.f));
	CImage * HeatOffsetTextureImage = CTextureLoader::loadImage("HeatOffset.bmp");
	STextureCreationFlags Flags;
	Flags.Filter = GL_LINEAR;
	Flags.MipMaps = false;
	Flags.Wrap = GL_MIRRORED_REPEAT;

	HeatOffsetTexture = new CTexture(HeatOffsetTextureImage, Flags);


	CImage * WaterOffsetTextureImage = CTextureLoader::loadImage("WaterOffset.bmp");
	WaterOffsetTexture = new CTexture(WaterOffsetTextureImage, Flags);

	ScratchTarget1 = new CFrameBufferObject();
	ScratchTexture1 = new CTexture(SceneManager->getScreenSize(), true, Flags);
	ScratchTarget1->attach(ScratchTexture1, GL_COLOR_ATTACHMENT0);

	BloomResultTarget = new CFrameBufferObject();
	BloomResultTexture = new CTexture(SceneManager->getScreenSize(), true);
	BloomResultTarget->attach(BloomResultTexture, GL_COLOR_ATTACHMENT0);

	SRenderPass DefaultPass;
	DefaultPass.Pass = ERenderPass::Default;
	DefaultPass.Target = SceneManager->getSceneFrameBuffer();

	RenderPasses.push_back(DefaultPass);

	Loaded = BlendShader && QuadCopy;

	if (! Loaded)
		std::cerr << "Failed to load required shaders for effects manager - all effects disabled." << std::endl;
}

#include <CApplication.h>


bool const CSceneEffectManager::isLoaded() const
{
	return Loaded;
}

void CSceneEffectManager::apply()
{
	if (isEffectEnabled(ESE_SSAO))
	{
		// Draw SSAO effect
		SPostProcessPass SSAOPass;
		SSAOPass.Textures["normalMap"] = NormalPassTexture;
		SSAOPass.Textures["rnm"] = RandomNormalsTexture;
		SSAOPass.Target = SSAOResultTarget;
		SSAOPass.Shader = SSAOShader;

		SSAOPass.doPass();

		if (isEffectEnabled(ESE_SSAO_BLUR))
		{
			SPostProcessPass SSAOBlurPass1;
			SSAOBlurPass1.Textures["uTexColor"] = SSAOResultTexture;
			SSAOBlurPass1.Target = ScratchTarget1;
			SSAOBlurPass1.Shader = BlurVertical;

			SSAOBlurPass1.doPass();


			SPostProcessPass SSAOBlurPass2;
			SSAOBlurPass2.Textures["uTexColor"] = ScratchTexture1;
			SSAOBlurPass2.Target = SSAOResultTarget;
			SSAOBlurPass2.Shader = BlurHorizontal;
			SSAOBlurPass2.Floats["DimAmount"] = 1.f;
			SSAOBlurPass2.Floats["BlurSize"] = 1.f;

			SSAOBlurPass2.doPass();
		}
	}

	if (isEffectEnabled(ESE_BLOOM))
	{
		// BLUR H
		SPostProcessPass BloomBlurPass1;
		BloomBlurPass1.Textures["uTexColor"] = SceneManager->getSceneFrameTexture();
		BloomBlurPass1.Target = ScratchTarget1;
		BloomBlurPass1.Shader = BlurHorizontal;
		BloomBlurPass1.Floats["DimAmount"] = 1.0f;
		BloomBlurPass1.Floats["BlurSize"] = 0.9f;

		BloomBlurPass1.doPass();

		// BLUR V
		SPostProcessPass BloomBlurPass2;
		BloomBlurPass2.Textures["uTexColor"] = ScratchTexture1;
		BloomBlurPass2.Target = BloomResultTarget;
		BloomBlurPass2.Shader = BlurVertical;
		BloomBlurPass2.Floats["DimAmount"] = 1.0f;
		BloomBlurPass2.Floats["BlurSize"] = 1.6f;

		BloomBlurPass2.doPass();
	}

	if (EnabledEffects)
	{
		// Final Blend
		SPostProcessPass BlendPass;
		BlendPass.Textures["scene"] = SceneManager->getSceneFrameTexture();
		BlendPass.Textures["ssao"] = isEffectEnabled(ESE_SSAO) ? SSAOResultTexture : White;
		BlendPass.Textures["bloom"] =  isEffectEnabled(ESE_BLOOM) ? BloomResultTexture : Magenta;
		BlendPass.Target = ScratchTarget1;
		BlendPass.Shader = BlendShader;

		BlendPass.doPass();

		// Copy results back into scene
		SPostProcessPass FinalPass;
		FinalPass.Textures["uTexColor"] = ScratchTexture1;
		FinalPass.Target = SceneManager->getSceneFrameBuffer();
		if (isEffectEnabled(ESE_HEAT_WAVE) || isEffectEnabled(ESE_WATER_DISTORT))
		{
			Timer += CApplication::get().getElapsedTime();

			if (isEffectEnabled(ESE_HEAT_WAVE))
				FinalPass.Textures["uHeatOffset"] = HeatOffsetTexture;
			else if (isEffectEnabled(ESE_WATER_DISTORT))
				FinalPass.Textures["uHeatOffset"] = WaterOffsetTexture;

			FinalPass.Floats["uTimer"] = Timer * 0.04f;
			FinalPass.Target = SceneManager->getSceneFrameBuffer();
			FinalPass.Shader = HeatCopy;
		}
		else
		{
			FinalPass.Shader = QuadCopy;
		}

		FinalPass.doPass();
	}
}

void CSceneEffectManager::setEffectEnabled(ESceneEffect const Effect, bool const Enabled)
{
	if (Enabled)
	{
		if (Effect)
			EnabledEffects |= Effect;
		else
			EnabledEffects = -1;
	}
	else
	{
		if (Effect)
			EnabledEffects ^= Effect;
		else
			EnabledEffects = 0;
	}

	switch (Effect)
	{
	case ESE_SSAO:
		{
			SRenderPass normalsPass;
			normalsPass.Pass = ERenderPass::ModelSpaceNormals;
			normalsPass.Target = NormalPassTarget;

			if (Enabled)
			{
				RenderPasses.push_back(normalsPass);

				if (! NormalPassTarget)
				{
					NormalPassTarget = new CFrameBufferObject();
					NormalPassTexture = new CTexture(SceneManager->getScreenSize(), true);
					NormalPassTarget->attach(NormalPassTexture, GL_COLOR_ATTACHMENT0);
					NormalPassTarget->attach(new CRenderBufferObject(GL_DEPTH_COMPONENT, SceneManager->getScreenSize()), GL_DEPTH_ATTACHMENT);

					SSAOResultTarget = new CFrameBufferObject();
					SSAOResultTexture = new CTexture(SceneManager->getScreenSize(), true);
					SSAOResultTarget->attach(SSAOResultTexture, GL_COLOR_ATTACHMENT0);

					RandomNormalsTexture = CTextureLoader::loadTexture("SSAO/RandNormals.bmp");
				}
			}
			else
			{
				RenderPasses.erase(std::remove(RenderPasses.begin(), RenderPasses.end(), normalsPass), RenderPasses.end());
			}

			break;
		}
	case ESE_SSAO_BLUR:
		break;

	case ESE_BLOOM:
		break;

	}
}

bool const CSceneEffectManager::isEffectEnabled(ESceneEffect const Effect)
{
	return (EnabledEffects & Effect) != 0;
}
