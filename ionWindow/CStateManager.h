#ifndef _CABBAGE_FRAMEKWORK_CSTATEMANAGER_H_INCLUDED_
#define _CABBAGE_FRAMEKWORK_CSTATEMANAGER_H_INCLUDED_

#include <sigslot/sigslot.h>

#include "CEventManager.h"
#include "CApplication.h"


class IState : public sigslot::has_slots<>
{

public:

    virtual void begin() =0;
    virtual void end() =0;

    virtual void OnGameTickStart(float const Elapsed) =0;
    virtual void OnGameTickEnd(float const Elapsed) =0;

    virtual void OnRenderStart(float const Elapsed) =0;
    virtual void OnRenderEnd(float const Elapsed) =0;

    virtual void OnMouseEvent(SMouseEvent const & Event) =0;
    virtual void OnKeyboardEvent(SKeyboardEvent const & Event) =0;

};

class CSceneManager;

template <class TImplementation>
class CState : public IState
{

protected:

	CApplication & Application;
	CSceneManager & SceneManager;

public:

    static TImplementation & get()
    {
        static TImplementation * Instance;

		if (! Instance)
			Instance = new TImplementation();

        return * Instance;
    }

	CState()
		: Application(CApplication::get()), SceneManager(CApplication::get().getSceneManager())
	{}


    virtual void begin()
    {}
    virtual void end()
    {}


    virtual void OnGameTickStart(float const Elapsed)
    {}
    virtual void OnGameTickEnd(float const Elapsed)
    {}


    virtual void OnRenderStart(float const Elapsed)
    {}
    virtual void OnRenderEnd(float const Elapsed)
    {}


    virtual void OnMouseEvent(SMouseEvent const & Event)
    {}
    virtual void OnKeyboardEvent(SKeyboardEvent const & Event)
    {}

};

class CApplication;

class CStateManager : public CApplicationEventReceiver
{

    friend class CApplication;

    CStateManager();

    IState * CurrentState;

public:

    void OnGameTickStart(float const Elapsed);
    void OnGameTickEnd(float const Elapsed);

    void OnRenderStart(float const Elapsed);
    void OnRenderEnd(float const Elapsed);

    void OnMouseEvent(SMouseEvent const & Event);
    void OnKeyboardEvent(SKeyboardEvent const & Event);

    void setState(IState * State);
    IState * NextState;
    void doStateChange();

	void shutDown();

};

#endif
