
#pragma once

#include <ionCore.h>
#include <ionWindow.h>

#include "IEventListener.h"


class IState : public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>, public IEventListener<SWindowResizedEvent>
{

public:

    virtual void Begin() = 0;
    virtual void End() = 0;
    virtual void Update(f32 const Elapsed) = 0;

};
