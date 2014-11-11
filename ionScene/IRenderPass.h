
#pragma once

#include <ionAsset.h>


class IRenderPass
{

public:

	CFrameBuffer * GetTarget();

	void Setup();
	void SetClearBuffers(vector<ion::GL::EBuffer> const & ClearBuffers);

	string const & GetName() const;

protected:

	vector<ion::GL::EBuffer> ClearBuffers;
	string Name;

	CFrameBuffer * Target = nullptr;

private:

	friend class CRenderPassManager;
	IRenderPass(string const & Name, CFrameBuffer * Target);

};
