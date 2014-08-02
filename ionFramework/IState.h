
#pragma once

#include <ionCore.h>

#include "IEventListener.h"


class IState : public IEventListener
{

public:

	virtual void Begin()
	{}

	virtual void End()
	{}

	virtual void Update(f32 const ElapsedTime)
	{}

};
