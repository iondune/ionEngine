
#pragma once

#include <ionAsset.h>


class IRenderPass
{

public:

	static IRenderPass * GetDefaultForwardShadingPass();

	IRenderPass(CFrameBuffer * Target);

	CFrameBuffer * GetTarget();

private:

	CFrameBuffer * Target = nullptr;

};
