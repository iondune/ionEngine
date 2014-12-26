#pragma once

#include <ionFramework.h>
#include <ionWindow.h>


template <class TContext>
class CContextObject
{

public:

	SingletonPointer<TContext> Context;

};


struct NullContext : public Singleton<NullContext>
{};

template <class TImplementation, class TContext = NullContext>
class CContextState : public IState, public Singleton<TImplementation>, CContextObject<TContext>
{

public:

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CTimeManager> TimeManager;
	SingletonPointer<CStateManager> StateManager;

};
