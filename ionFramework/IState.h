
#pragma once

#include <ionCore.h>

#include "IEventListener.h"
#include "SKeyboardEvent.h"
#include "SMouseEvent.h"
#include "SWindowResizedEvent.h"


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
