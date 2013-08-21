
#pragma once

#include "IState.h"


class CWindow;

class CStateManager : public Singleton<CStateManager>, public IEventListener<SKeyboardEvent>, public IEventListener<SMouseEvent>, public IEventListener<SWindowResizedEvent>
{

    friend class Singleton<CStateManager>;

public:

    void SetState(IState * State);
    void DoStateChange();

	void Update(f32 const ElapsedTime);

	void Connect(CWindow * Window);
	void ShutDown();

	void OnEvent(SMouseEvent & Event);
	void OnEvent(SKeyboardEvent & Event);
	void OnEvent(SWindowResizedEvent & Event);

private:

    CStateManager();

protected:

    IState * CurrentState;
    IState * NextState;

};
