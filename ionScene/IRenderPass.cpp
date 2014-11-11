
#include "IRenderPass.h"


IRenderPass::IRenderPass(string const & Name, CFrameBuffer * Target)
{
	this->ClearBuffers = { ion::GL::EBuffer::Color, ion::GL::EBuffer::Depth };
	this->Name = Name;
	this->Target = Target;
}

CFrameBuffer * IRenderPass::GetTarget()
{
	return Target;
}

void IRenderPass::SetClearBuffers(vector<ion::GL::EBuffer> const & ClearBuffers)
{
	this->ClearBuffers = ClearBuffers;
}

void IRenderPass::Setup()
{
	if (ClearBuffers.size())
		Target->Clear(ClearBuffers);
}

string const & IRenderPass::GetName() const
{
	return Name;
}
