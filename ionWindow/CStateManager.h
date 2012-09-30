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
	
	virtual void OnWindowResized(SWindowResizedEvent const & Event) =0;

};

class CSceneManager;

template <class TImplementation>
class Singleton
{

private:
	
	Singleton & operator = (Singleton const &);
	Singleton(Singleton const &);

protected:

	Singleton()
	{}

public:

    static TImplementation & get()
    {
        static TImplementation * Instance = 0;

		if (! Instance)
			Instance = new TImplementation();

        return * Instance;
    }

};

template <class TContext>
class CContextObject
{

protected:

	struct DisableAutoContextLoad
	{};

	TContext * Context;

	CContextObject()
		: Context(0)
	{
		loadContext();
	}

	CContextObject(DisableAutoContextLoad)
		: Context(0)
	{}

public:

	virtual void loadContext()
	{
		Context = & TContext::get();
	}

};

template <class TContext>
class CApplicationContextObject : public CContextObject<TContext>
{

protected:

	CApplication * Application;
	CSceneManager * SceneManager;

	CApplicationContextObject()
		: Application(0), SceneManager(0), CContextObject<TContext>(DisableAutoContextLoad())
	{
		loadContext();
	}

	CApplicationContextObject(DisableAutoContextLoad)
		: Application(0), SceneManager(0)
	{
	}

public:

	virtual void loadContext()
	{
		CContextObject<TContext>::loadContext();
		Application = & CApplication::get();
		SceneManager = & Application->getSceneManager();
	}

};

template <class TImplementation, class TContext>
class CContextState : public IState, public Singleton<TImplementation>, public CApplicationContextObject<TContext>
{

protected:

	CContextState()
	{}

	CContextState(DisableAutoContextLoad)
		: CApplicationContextObject<TContext>(DisableAutoContextLoad)
	{}

public:

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

    virtual void OnWindowResized(SWindowResizedEvent const & Event)
    {}

};

struct NullContext
{};

template <class TImplementation>
class CState : public CContextState<TImplementation, NullContext>
{

protected:

	CState()
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

	void OnWindowResized(SWindowResizedEvent const & Event);

    void setState(IState * State);
    IState * NextState;
    void doStateChange();

	void shutDown();

};

#endif
