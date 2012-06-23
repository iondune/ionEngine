#include "CDeferredShadingManager.h"

#include "CSceneManager.h"
#include "CShaderLoader.h"

#include <CTextureLoader.h>

CDeferredShadingManager::CDeferredShadingManager(CSceneManager * sceneManager)
	: CSceneEffectManager(sceneManager), OverlayColor(1.f, 1.f, 1.f)
{

	DeferredOutputTarget = new CFrameBufferObject();
	DeferredColorOutput = new CTexture(SceneManager->getScreenSize(), false);
	STextureCreationFlags Flags;
	Flags.MipMaps = false;
	//Flags.PixelFormat = GL_RED;
	Flags.PixelInternalFormat = GL_RGB32F;
	Flags.PixelType = GL_FLOAT;
	DeferredPositionOutput = new CTexture(SceneManager->getScreenSize(), false, Flags);
	DeferredNormalOutput = new CTexture(SceneManager->getScreenSize(), false);

	DeferredOutputTarget->attach(DeferredColorOutput, GL_COLOR_ATTACHMENT0);
	DeferredOutputTarget->attach(DeferredPositionOutput, GL_COLOR_ATTACHMENT1);
	DeferredOutputTarget->attach(DeferredNormalOutput, GL_COLOR_ATTACHMENT2);
	DeferredOutputTarget->attach(new CRenderBufferObject(GL_DEPTH_COMPONENT, SceneManager->getScreenSize()), GL_DEPTH_ATTACHMENT);

	LightPassOutputTarget = new CFrameBufferObject();
	LightPassColorOutput = new CTexture(SceneManager->getScreenSize(), false);
	LightPassOutputTarget->attach(LightPassColorOutput, GL_COLOR_ATTACHMENT0);


	DeferredOutputTarget->bind();
	GLenum Buffers[] = 
	{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2
	};

	glDrawBuffers(sizeof(Buffers)/sizeof(GLenum), Buffers);


	RenderPasses.clear();

	SRenderPass DeferredPass;
	DeferredPass.Pass = ERenderPass::DeferredColors;
	DeferredPass.Target = DeferredOutputTarget;

	RenderPasses.push_back(DeferredPass);


	SRenderPass LightPass;
	LightPass.Pass = ERenderPass::DeferredLights;
	LightPass.Target = LightPassOutputTarget;

	RenderPasses.push_back(LightPass);


	FinalBlendShader = CShaderLoader::loadShader("Deferred/Blend");
	OverlayShader = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "FBO/OverlayCopy.frag");
}

#include <CApplication.h>

void CDeferredShadingManager::apply()
{
#if 0
	SPostProcessPass BlendPass;
	BlendPass.Textures["uTexColor"] = DeferredPositionOutput;
	//BlendPass.Textures["uLightPass"] = LightPassColorOutput;
	BlendPass.Target = SceneManager->getSceneFrameBuffer();
	BlendPass.Shader = CShaderLoader::loadShader("FBO/QuadCopy");//FinalBlendShader;
#else
	SPostProcessPass BlendPass;
	BlendPass.Textures["uSceneColor"] = DeferredColorOutput;
	BlendPass.Textures["uLightPass"] = LightPassColorOutput;
	BlendPass.Target = ScratchTarget1;
	BlendPass.Shader = FinalBlendShader;
#endif

	BlendPass.doPass();

	// Copy results back into scene
	SPostProcessPass FinalPass;
	FinalPass.Textures["uTexColor"] = ScratchTexture1;
	FinalPass.Target = BloomResultTarget; // heehee

	if (isEffectEnabled(ESE_HEAT_WAVE) || isEffectEnabled(ESE_WATER_DISTORT))
	{
		Timer += CApplication::get().getElapsedTime();

		if (isEffectEnabled(ESE_HEAT_WAVE))
			FinalPass.Textures["uHeatOffset"] = HeatOffsetTexture;
		else if (isEffectEnabled(ESE_WATER_DISTORT))
			FinalPass.Textures["uHeatOffset"] = WaterOffsetTexture;

		FinalPass.Floats["uTimer"] = Timer * 0.04f;
		FinalPass.Shader = HeatCopy;
	}
	else
	{
		FinalPass.Shader = QuadCopy;
	}

	FinalPass.doPass();

	SPostProcessPass ActualFinalPass;
	ActualFinalPass.Textures["uTexColor"] = BloomResultTexture;
	ActualFinalPass.Target = SceneManager->getSceneFrameBuffer();
	ActualFinalPass.Colors["uOverlayColor"] = OverlayColor;
	ActualFinalPass.Shader = OverlayShader;
	ActualFinalPass.doPass();

}
