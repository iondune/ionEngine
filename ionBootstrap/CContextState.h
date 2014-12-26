#pragma once

#include <ionFramework.h>
#include <ionWindow.h>


struct NullContext : public Singleton<NullContext>
{};

template <class TImplementation, class TContext = NullContext>
class CContextState : public IState, public Singleton<TImplementation>
{

protected:

	CContextState()
		: Context()
	{
		LoadContext();
	}

	TContext * Context;

public:

	virtual void LoadContext()
	{
		Context = TContext::GetPtr();
	}

	SingletonPointer<CWindowManager> WindowManager;
	SingletonPointer<CSceneManager> SceneManager;
	SingletonPointer<CTimeManager> TimeManager;
	SingletonPointer<CStateManager> StateManager;

};
