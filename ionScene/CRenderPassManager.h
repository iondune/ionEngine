
#pragma once

#include "IRenderPass.h"


class CRenderPassManager
{

public:

	//! Checks the configuration of this render pass manager
	//! If no configuration is supplied, it automatically builds a default one
	void CheckConfiguration();

	IRenderPass * GetRenderPass(string const & Name);
	IRenderPass * AddRenderPass(string const & Name, CFrameBuffer * Target);

	vector<IRenderPass *> const & GetOrderedRenderPasses();
	void SetRenderPassOrder(std::initializer_list<string> Order);

protected:

	map<string, IRenderPass *> RenderPasses;
	vector<IRenderPass *> OrderedRenderPasses;

};
