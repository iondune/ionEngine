
#pragma once

#include <ionCore.h>


class IState : public IEventListener
{

public:

	virtual void Begin()
	{}

	virtual void End()
	{}

	virtual void Update(float const ElapsedTime)
	{}

};
