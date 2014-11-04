
#include "CRenderPassManager.h"


void CRenderPassManager::CheckConfiguration()
{
	if (RenderPasses.size() == 0)
	{
		RenderPasses["Default"] = new IRenderPass{"Default", CFrameBuffer::GetDefaultFrameBuffer()};
	}

	if (OrderedRenderPasses.size() == 0)
	{
		if (RenderPasses.size() > 1)
			cerr << "Warning: No render pass order specified, generating fallback using alphabetical (probably not was intended)." << endl;

		OrderedRenderPasses.clear();
		for (auto RenderPassIterator : RenderPasses)
			OrderedRenderPasses.push_back(RenderPassIterator.second);
	}
}

IRenderPass * CRenderPassManager::GetRenderPass(string const & Name)
{
	return ConditionalMapAccess(RenderPasses, Name);
}

IRenderPass * CRenderPassManager::AddRenderPass(string const & Name, CFrameBuffer * Target)
{
	OrderedRenderPasses.clear();
	return RenderPasses[Name] = new IRenderPass{Name, Target};
}

vector<IRenderPass *> const & CRenderPassManager::GetOrderedRenderPasses()
{
	return OrderedRenderPasses;
}

void CRenderPassManager::SetRenderPassOrder(std::initializer_list<string> Order)
{
	OrderedRenderPasses.clear();

	if (Order.size() != RenderPasses.size())
	{
		cerr << "Warning: Render pass order list does not match size of render pass configuration." << endl;
		return;
	}

	for (auto Label : Order)
	{
		IRenderPass * Pass = nullptr;
		if (TryMapAccess(RenderPasses, Label, Pass))
			OrderedRenderPasses.push_back(Pass);
		else
		{
			cerr << "Warning: Cannot find render pass with name: " << Label << endl;
			OrderedRenderPasses.clear();
			return;
		}
	}
}
