
#pragma once

#include <ionCore.h>
#include <ionWindow.h>

#include "IEventListener.h"


class IState : public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>, public IEventListener<SWindowResizedEvent>
{

public:

	virtual void Begin()
	{}

	virtual void End()
	{}

	virtual void Update(f32 const ElapsedTime)
	{}

	virtual void OnEvent(SKeyboardEvent & Event)
	{}

	virtual void OnEvent(SMouseEvent & Event)
	{}

	virtual void OnEvent(SWindowResizedEvent & Event)
	{}

};
