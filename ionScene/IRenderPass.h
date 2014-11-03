
#pragma once

#include <ionAsset.h>


class IRenderPass
{

public:
	
	static IRenderPass * GetDefaultForwardShadingPass();
	static IRenderPass * GetDefaultPostProcessPass();

	IRenderPass(CFrameBuffer * Target);

	CFrameBuffer * GetTarget();

	void Setup();
	void SetClearTarget(bool const ClearTarget);

protected:

	bool ClearTarget = true;

	CFrameBuffer * Target = nullptr;

};
