#include "CFadeOutState.h"

#include <CSceneManager.h>
#include <CTextureLoader.h>

#include "CApplication.h"


CFadeOutState::CFadeOutState(IState * nextState, float const fadeTime)
	: NextState(nextState), FadeTime(fadeTime)
{}

void CFadeOutState::begin()
{
	SourceFrameBuffer = new CFrameBufferObject();
	STextureCreationFlags Flags;
	Flags.MipMaps = false;
	SourceFrameTexture = new CTexture(CApplication::get().getWindowSize(), true, Flags);
	SourceFrameBuffer->attachColorTexture(SourceFrameTexture, 0);

	CSceneEffectManager::SPostProcessPass GetSceneBuffer;
	GetSceneBuffer.Shader = CShaderLoader::loadShader("FBO/QuadCopy");
	GetSceneBuffer.Textures["uTexColor"] = CApplication::get().getSceneManager().getSceneFrameTexture();
	GetSceneBuffer.Target = SourceFrameBuffer;

	GetSceneBuffer.doPass();

	TotalRunTime = 0.f;
}

void CFadeOutState::end()
{
	delete SourceFrameTexture;
	delete SourceFrameBuffer;

	delete this;
}


void CFadeOutState::OnGameTickStart(float const Elapsed)
{}

void CFadeOutState::OnGameTickEnd(float const Elapsed)
{}


void CFadeOutState::OnRenderStart(float const Elapsed)
{
	TotalRunTime += Elapsed;

	if (TotalRunTime > FadeTime)
	{
		TotalRunTime = FadeTime;
		CApplication::get().getStateManager().setState(NextState);
	}
	
	CSceneEffectManager::SPostProcessPass DrawFrame;

	float Dim = 1.f - TotalRunTime / FadeTime;
	float FinalBlurSize = TotalRunTime / 0.1f;

	DrawFrame.Shader = CShaderLoader::loadShader("FBO/QuadCopyUV.glsl", "BlurH.frag");
	DrawFrame.Floats["BlurSize"] = FinalBlurSize;
	DrawFrame.Floats["DimAmount"] = Dim;
	DrawFrame.Textures["uTexColor"] = SourceFrameTexture;

	DrawFrame.doPass();

	CApplication::get().swapBuffers();
}

void CFadeOutState::OnRenderEnd(float const Elapsed)
{}


void CFadeOutState::OnMouseEvent(SMouseEvent const & Event)
{}

void CFadeOutState::OnKeyboardEvent(SKeyboardEvent const & Event)
{}
