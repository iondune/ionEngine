
#include "IRenderPass.h"


IRenderPass * IRenderPass::GetDefaultForwardShadingPass()
{
	static IRenderPass * DefaultForwardShadingPass = nullptr;
	
	if (! DefaultForwardShadingPass)
		DefaultForwardShadingPass = new IRenderPass{CFrameBuffer::GetDefaultFrameBuffer()};

	return DefaultForwardShadingPass;
}

IRenderPass::IRenderPass(CFrameBuffer * Target)
{
	this->Target = Target;
}

CFrameBuffer * IRenderPass::GetTarget()
{
	return Target;
}
