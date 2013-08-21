
#pragma once

#include "IState.h"


class CWindow;

class CStateManager : public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>, public IEventListener<SWindowResizedEvent>
{

    friend class CApplication;

public:

    void SetState(IState * State);
    void DoStateChange();

	void Connect(CWindow * Window);
	void ShutDown();

private:

    CStateManager();

protected:

    IState * CurrentState;
    IState * NextState;

};
