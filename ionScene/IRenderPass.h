
#pragma once

#include <ionAsset.h>


class IRenderPass
{

public:

	CFrameBuffer * GetTarget();

	void Setup();
	void SetClearTarget(bool const ClearTarget);

	string const & GetName() const;

protected:

	bool ClearTarget = true;
	string Name;

	CFrameBuffer * Target = nullptr;

private:

	friend class CRenderPassManager;
	IRenderPass(string const & Name, CFrameBuffer * Target);

};
