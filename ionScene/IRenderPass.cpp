
#include "IRenderPass.h"


IRenderPass::IRenderPass(string const & Name, CFrameBuffer * Target)
{
	this->Name = Name;
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

string const & IRenderPass::GetName() const
{
	return Name;
}
