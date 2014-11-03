
#include "IRenderPass.h"


IRenderPass * IRenderPass::GetDefaultForwardShadingPass()
{
	static IRenderPass * DefaultForwardShadingPass = nullptr;
	
	if (! DefaultForwardShadingPass)
		DefaultForwardShadingPass = new IRenderPass{CFrameBuffer::GetDefaultFrameBuffer()};

	return DefaultForwardShadingPass;
}

IRenderPass * IRenderPass::GetDefaultPostProcessPass()
{
	static IRenderPass * DefaultPostProcessPass = nullptr;
	
	if (! DefaultPostProcessPass)
	{
		DefaultPostProcessPass = new IRenderPass{CFrameBuffer::GetDefaultFrameBuffer()};
		DefaultPostProcessPass->SetClearTarget(false);
	}

	return DefaultPostProcessPass;
}

IRenderPass::IRenderPass(CFrameBuffer * Target)
{
	this->Target = Target;
}

CFrameBuffer * IRenderPass::GetTarget()
{
	return Target;
}

void IRenderPass::SetClearTarget(bool const ClearTarget)
{
	this->ClearTarget = ClearTarget;
}

void IRenderPass::Setup()
{
	if (ClearTarget)
		Target->Clear();
}
